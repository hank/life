#include <clutter/clutter.h>
#include <stdlib.h>

ClutterActor * rect = NULL;

guint32 on_alpha(ClutterAlpha * alpha, gpointer data)
{
  /* Get the timeline position on which to base the value */
  ClutterTimeline * timeline = clutter_alpha_get_timeline(alpha);
  const int current_frame_num = clutter_timeline_get_current_frame(timeline);
  const int n_frames = clutter_timeline_get_n_frames(timeline);

  return (CLUTTER_ALPHA_MAX_ALPHA * current_frame_num / n_frames);
}

int main(int argc, char ** argv) 
{
  ClutterColor stage_color = {0x00, 0x00, 0x00, 0xFF};
  ClutterColor rect_color  = {0xFF, 0xFF, 0xFF, 0x99};

  clutter_init(&argc, &argv);

  ClutterActor * stage = clutter_stage_get_default();
  clutter_actor_set_size(stage, 200, 200);
  clutter_stage_set_color(CLUTTER_STAGE(stage), &stage_color);

  rect = clutter_rectangle_new_with_color(&rect_color);
  clutter_actor_set_size(rect, 40, 40);
  clutter_actor_set_position(rect, 10, 10);
  clutter_container_add_actor(CLUTTER_CONTAINER(stage), rect);
  clutter_actor_show(rect);

  clutter_actor_show(stage);

  ClutterScore * score = clutter_score_new();
  clutter_score_set_loop(score, TRUE);

  ClutterTimeline * timeline1 = clutter_timeline_new(100, 30);
  clutter_score_append(score, NULL, timeline1);

  ClutterTimeline * timeline2 = clutter_timeline_new(100, 30);
  clutter_score_append(score, timeline1, timeline2);

  ClutterEffectTemplate * effect_template = 
    clutter_effect_template_new(timeline1, &on_alpha);
  ClutterKnot knot[2];
  knot[0].x = 10;
  knot[0].y = 10;
  knot[1].x = 150;
  knot[1].y = 150;

  ClutterEffectTemplate * effect_template2 = 
    clutter_effect_template_new(timeline2, &on_alpha);
  ClutterKnot knot2[2];
  knot2[0].x = 150;
  knot2[0].y = 150;
  knot2[1].x = 150;
  knot2[1].y = 10;

  clutter_effect_path(effect_template, rect, knot, 
    (sizeof(knot) / sizeof(ClutterKnot)), NULL, NULL);

  clutter_effect_path(effect_template2, rect, knot2, 
    (sizeof(knot2) / sizeof(ClutterKnot)), NULL, NULL);

  clutter_effect_fade(effect_template, rect, 50, NULL, NULL);
  clutter_effect_fade(effect_template2, rect, 50, NULL, NULL);

  clutter_score_start(score);

  g_object_unref(effect_template);
  g_object_unref(timeline1);
  g_object_unref(timeline2);

  clutter_main();

  return EXIT_SUCCESS;
}
