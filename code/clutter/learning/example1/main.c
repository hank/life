#include <clutter/clutter.h>
#include <stdlib.h>

on_stage_button_press(ClutterStage * stage, ClutterEvent * event, gpointer data){
  gint x = 0;
  gint y = 0;
  clutter_event_get_coords(event, &x, &y);

  g_print("Stage clicked at (%d, %d)\n", x, y);

  return TRUE; /* Stops further event handling */
}

int main(int argc, char * argv[]) {
  ClutterColor stage_color = {0x00, 0x00, 0x00, 0xFF};
  clutter_init(&argc, &argv);
 
  /* Get the stage and get its size and color */
  ClutterActor * stage = clutter_stage_get_default();
  clutter_actor_set_size(stage, 200, 200);
  clutter_stage_set_color(CLUTTER_STAGE(stage), &stage_color);

  /* Show the stage */
  clutter_actor_show(stage);

  /* Connect a signal handler for mouse clicks */
  g_signal_connect(stage, "button-press-event", 
    G_CALLBACK(on_stage_button_press), NULL);

  /* Start the main loop */
  clutter_main();

  return EXIT_SUCCESS;
}
