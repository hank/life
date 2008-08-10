#include <clutter/clutter.h>
#include <stdlib.h>

ClutterActor * rect = NULL;

gint rotation_angle = 0;
gint color_change_count = 0;

void on_timeline_new_frame(ClutterTimeline * timeline, gint frame_num, 
                           gpointer data)
{
  if((++rotation_angle) >= 360) rotation_angle = 0;
  clutter_actor_set_rotation(rect, CLUTTER_X_AXIS, rotation_angle, 0, 0, 0);
  if((++color_change_count) >= 100) color_change_count = 0;
  if(color_change_count == 0) {
    ClutterColor color = {0xFF, 0xFF, 0xFF, 0xFF}; //White
    clutter_rectangle_set_color(CLUTTER_RECTANGLE(rect), &color);
  } 
  else if(color_change_count == 50) {
    ClutterColor color = {0x00, 0xFF, 0xFF, 0xFF}; //Purple
    clutter_rectangle_set_color(CLUTTER_RECTANGLE(rect), &color);
  }
}

int main(int argc, char ** argv)
{
  ClutterColor stage_color = {0x00, 0x00, 0x00, 0xFF}; // Black
  ClutterColor rect_color = {0x00, 0xFF, 0xFF, 0xFF}; // Purple

  clutter_init(&argc, &argv);

  ClutterActor * stage = clutter_stage_get_default();
  clutter_actor_set_size(stage, 200, 200);
  clutter_stage_set_color(CLUTTER_STAGE(stage), &stage_color);

  rect = clutter_rectangle_new_with_color(&rect_color);
  clutter_actor_set_size(rect, 70, 70);
  clutter_actor_set_position(rect, 50, 100);
  clutter_container_add_actor(CLUTTER_CONTAINER(stage), rect);
  clutter_actor_show(rect);

  clutter_actor_show(stage);

  ClutterTimeline * timeline = clutter_timeline_new(10, //frames
    120 //fps
  );
  g_signal_connect(timeline, "new-frame", 
    G_CALLBACK(on_timeline_new_frame), NULL);
  clutter_timeline_set_loop(timeline, TRUE);
  clutter_timeline_start(timeline);
  clutter_main();

  g_object_unref(timeline);

  return EXIT_SUCCESS;
}
