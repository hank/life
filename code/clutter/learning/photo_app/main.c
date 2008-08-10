#include <clutter/clutter.h>
#include <stdlib.h>

ClutterActor * stage = NULL;
ClutterActor * label_filename = NULL;
ClutterTimeline * timeline_rotation = NULL;
ClutterTimeline * timeline_moveup = NULL;
ClutterBehaviour * behaviour_scale = NULL;
ClutterBehaviour * behaviour_path = NULL;
ClutterBehaviour * behaviour_opacity = NULL;

const gint ELLIPSE_Y = 390;
const gint ELLIPSE_HEIGHT = 450;
const gint IMAGE_HEIGHT = 100;

static gboolean on_texture_button_press(ClutterActor * actor, 
  ClutterEvent * event, gpointer data);

const double angle_step = 30;

typedef struct Item {
  ClutterActor * actor;
  ClutterBehaviour * ellipse_behaviour;
  gchar * filepath;
} Item;

Item * item_at_front = NULL;

GSList * list_items = 0;

void on_foreach_clear_list_items(gpointer data, gpointer user_data)
{
  Item * item = (Item *)data;
  g_object_unref(item->ellipse_behaviour);
  g_free(item->filepath);
  g_free(item);
}

void scale_texture_default(ClutterActor * texture)
{
  int pixbuf_height = 0;
  clutter_texture_get_base_size(CLUTTER_TEXTURE(texture), NULL, &pixbuf_height);
  const gdouble scale = pixbuf_height ? 
      IMAGE_HEIGHT / (gdouble)pixbuf_height : 
      0;
  clutter_actor_set_scale(texture, scale, scale);
}

void load_images(const gchar * directory_path)
{
  g_return_if_fail(directory_path);
  g_slist_foreach(list_items, on_foreach_clear_list_items, NULL);
  g_slist_free(list_items);

  list_items = NULL;

  GError * error = NULL;
  GDir * dir = g_dir_open(directory_path, 0, &error);
  if(error) {
    g_warning("g_dir_open() failed: %s\n", error->message);
    g_clear_error(&error);
    return;
  }

  const gchar * filename = NULL;
  while( (filename = g_dir_read_name(dir)) ) {
    gchar * path = g_build_filename(directory_path, filename, NULL);

    /* Try to load the file as an image */
    ClutterActor * actor = clutter_texture_new_from_file(path, NULL);
    if(actor) {
      Item * item = g_new0(Item, 1);
      item->actor = actor;
      item->filepath = g_strdup(path);
      
      /* Make sure all images are scaled to the same height */
      scale_texture_default(item->actor);
      list_items = g_slist_append(list_items, item);
    }
    g_free(path);
  }
}

void add_to_ellipse_behaviour(ClutterTimeline * timeline_rotation,
  gdouble start_angle, Item * item)
{
  g_return_if_fail(timeline_rotation);

  ClutterAlpha * alpha = clutter_alpha_new_full(timeline_rotation,
    CLUTTER_ALPHA_SINE_INC, NULL, NULL);
  item->ellipse_behaviour = clutter_behaviour_ellipse_new(
    alpha, 320, ELLIPSE_Y, ELLIPSE_HEIGHT, ELLIPSE_HEIGHT,
    CLUTTER_ROTATE_CW, start_angle, start_angle + 360
  );
  clutter_behaviour_ellipse_set_angle_tilt(
    CLUTTER_BEHAVIOUR_ELLIPSE(item->ellipse_behaviour),
    CLUTTER_X_AXIS, -90);

  clutter_behaviour_apply(item->ellipse_behaviour, item->actor);
}

void add_image_actors()
{
  int x = 20;
  int y = 0;
  gdouble angle = 0;
  GSList * list = list_items;
  while(list) {
    Item * item = list->data;
    ClutterActor * actor = item->actor;
    clutter_container_add_actor(CLUTTER_CONTAINER(stage), actor);
    clutter_actor_set_position(actor, x, y);
    y += 100;

    clutter_actor_set_reactive(actor, TRUE);
    g_signal_connect(actor, "button-press-event", 
      G_CALLBACK(on_texture_button_press), item);
    add_to_ellipse_behaviour(timeline_rotation, angle, item);
    angle += angle_step;
    clutter_actor_show(actor);
    list = g_slist_next(list);
  }
}

gdouble angle_in_360(gdouble angle)
{
  gdouble result = angle;
  while(result >= 360) result -= 360;
  return result;
}

void on_timeline_moveup_completed(ClutterTimeline * timeline, gpointer data)
{
  g_object_unref(timeline_moveup);
  timeline_moveup = NULL;
  g_object_unref(behaviour_scale);
  behaviour_scale = NULL;
  g_object_unref(behaviour_path);
  behaviour_path = NULL;
  g_object_unref(behaviour_opacity);
  behaviour_opacity = NULL;
}
void on_timeline_rotation_completed(ClutterTimeline * timeline, gpointer data)
{
  ClutterActor * actor = item_at_front->actor;
  timeline_moveup = clutter_timeline_new(60, 30);
  ClutterAlpha * alpha = clutter_alpha_new_full(timeline_moveup, 
    CLUTTER_ALPHA_SINE_INC, NULL, NULL);
  gdouble scale_start = 0;
  clutter_actor_get_scale(actor, &scale_start, NULL);
  const gdouble scale_end = scale_start * 1.8;
  behaviour_scale = clutter_behaviour_scale_new(alpha, scale_start, 
    scale_start, scale_end, scale_end);
  clutter_behaviour_apply(behaviour_scale, actor);

  ClutterKnot knots[2];
  knots[0].x = clutter_actor_get_x(actor);
  knots[0].y = clutter_actor_get_y(actor);
  knots[1].x = knots[0].x;
  knots[1].y = knots[0].y - 250;

  behaviour_path = clutter_behaviour_path_new(alpha, knots, 
    G_N_ELEMENTS(knots));
  clutter_behaviour_apply(behaviour_path, actor);

  clutter_label_set_text(CLUTTER_LABEL(label_filename), 
    item_at_front->filepath);
  behaviour_opacity = clutter_behaviour_opacity_new(alpha, 0, 255);
  clutter_behaviour_apply(behaviour_opacity, label_filename);

  g_signal_connect(timeline_moveup, "completed", 
    G_CALLBACK(on_timeline_moveup_completed), NULL);

  clutter_timeline_start(timeline_moveup);
}

void rotate_all_until_item_is_at_front(Item * item)
{
  g_return_if_fail(item);

  clutter_timeline_stop(timeline_rotation);
  if(timeline_moveup) clutter_timeline_stop(timeline_moveup);
  clutter_actor_set_opacity(label_filename, 0);
  
  const gint pos = g_slist_index(list_items, item);
  g_assert(pos != -1);

  if(!item_at_front && list_items) {
    item_at_front = (Item *)list_items->data;
  }

  gint pos_front = 0;
  if(item_at_front) pos_front = g_slist_index(list_items, item_at_front);
  g_assert(pos_front != -1);

  /* Calculate the end angle of the first item */
  const gdouble angle_front = 180;
  gdouble angle_start = angle_front - (angle_step * pos_front);
  angle_start = angle_in_360(angle_start);

  gdouble angle_end = angle_front - (angle_step * pos);

  gdouble angle_diff = 0;

  GSList * list = list_items;
  while(list) {
    Item * this_item = (Item *)list->data;
    scale_texture_default(this_item->actor);
    angle_start = angle_in_360(angle_start);
    angle_end = angle_in_360(angle_end);

    /* Move 360 instead of 0 if moving for the first time */
    if(item_at_front == item) angle_end += 360;
    clutter_behaviour_ellipse_set_angle_start(
      CLUTTER_BEHAVIOUR_ELLIPSE(this_item->ellipse_behaviour), angle_start);
    clutter_behaviour_ellipse_set_angle_end(
      CLUTTER_BEHAVIOUR_ELLIPSE(this_item->ellipse_behaviour), angle_end);
    
    if(this_item == item) {
      if(angle_start < angle_end) angle_diff = angle_end - angle_start;
      else angle_diff = 360 - (angle_start - angle_end);
    }
    angle_end += angle_step;
    angle_start += angle_step;
    list = g_slist_next(list);
  }

  /* Set the # of frames to be proportional to the distance to travel */
  gint pos_to_move = 0;
  if(pos_front < pos) {
    const gint count = g_slist_length(list_items);
    pos_to_move = count + (pos - pos_front);
  }
  else {
    pos_to_move = pos_front - pos;
  }

  clutter_timeline_set_n_frames(timeline_rotation, angle_diff);

  item_at_front = item;
  clutter_timeline_start(timeline_rotation);
}

static gboolean on_texture_button_press(ClutterActor * actor, 
  ClutterEvent * event, gpointer data)
{
  if(timeline_rotation && clutter_timeline_is_playing(timeline_rotation)) {
    printf("on_texture_button_press: ignoring.\n");
    return FALSE;
  }
  else {
    printf("on_texture_button_press: handling.\n");
  }
  Item * item = (Item *)data;
  rotate_all_until_item_is_at_front(item);

  return TRUE;
}

int main(int argc, char ** argv)
{
  ClutterColor stage_color = {0xB0, 0xB0, 0xB0, 0xFF};

  clutter_init(&argc, &argv);

  stage = clutter_stage_get_default();
  clutter_actor_set_size(stage, 800, 600);
  clutter_stage_set_color(CLUTTER_STAGE(stage), &stage_color);

  label_filename = clutter_label_new();
  ClutterColor label_color = {0x60, 0x60, 0x90, 0xFF};
  clutter_label_set_color(CLUTTER_LABEL(label_filename), &label_color);
  clutter_label_set_font_name(CLUTTER_LABEL(label_filename), "Sans 24");
  clutter_actor_set_position(label_filename, 10, 10);
  clutter_actor_set_opacity(label_filename, 0);
  clutter_container_add_actor(CLUTTER_CONTAINER(stage), label_filename);
  clutter_actor_show(label_filename);

  ClutterColor rect_color = {0xFF, 0xFF, 0xFF, 0xFF};
  ClutterActor * rect = clutter_rectangle_new_with_color(&rect_color);
  clutter_actor_set_height(rect, ELLIPSE_HEIGHT + 20);
  clutter_actor_set_width(rect, clutter_actor_get_width(stage) + 100);
  clutter_actor_set_position(rect, 
    -(clutter_actor_get_width(rect) - clutter_actor_get_width(stage))/2,
    ELLIPSE_Y + IMAGE_HEIGHT - clutter_actor_get_height(rect)/2
  );
  clutter_actor_set_rotation(rect, CLUTTER_X_AXIS, -90, 0, 
    (clutter_actor_get_height(rect)/2), 0);
  clutter_actor_show(rect);

  clutter_actor_show(stage);
  timeline_rotation = clutter_timeline_new(60, 30);
  g_signal_connect(timeline_rotation, "completed", 
    G_CALLBACK(on_timeline_rotation_completed), NULL);
  if(argc > 1) {
    load_images(argv[argc-1]);
  }
  else {
    load_images("./");
  }
  add_image_actors();
  if(list_items) rotate_all_until_item_is_at_front((Item *)list_items->data);

  clutter_main();

  g_slist_foreach(list_items, on_foreach_clear_list_items, NULL);
  g_slist_free(list_items);

  g_object_unref(timeline_rotation);

  return EXIT_SUCCESS;
}
