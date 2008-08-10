#include <clutter/clutter.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  ClutterColor stage_color = {0x00, 0x00, 0x00, 0xFF};
  ClutterColor actor_color = {0xFF, 0x00, 0x00, 0xFF};
  clutter_init(&argc, &argv);
 
  /* Get the stage and get its size and color */
  ClutterActor * stage = clutter_stage_get_default();
  clutter_actor_set_size(stage, 200, 200);
  clutter_stage_set_color(CLUTTER_STAGE(stage), &stage_color);

  ClutterActor * rect = clutter_rectangle_new_with_color(&actor_color);
  clutter_actor_set_size(rect, 100, 100);
  clutter_actor_set_position(rect, 20, 20);
  clutter_container_add_actor(CLUTTER_CONTAINER(stage), rect);
  clutter_actor_show(rect);

  // Add a label
  ClutterActor * label = clutter_label_new_full("Sans 12", "Some Text", 
    &actor_color);
  clutter_actor_set_size(label, 500, 500);
  clutter_actor_set_position(label, 20, 150);
  clutter_container_add_actor(CLUTTER_CONTAINER(stage), label);
  clutter_actor_show(label);

  /* Show the stage */
  clutter_actor_show(stage);

  /* Start the main loop */
  clutter_main();

  return EXIT_SUCCESS;
}
