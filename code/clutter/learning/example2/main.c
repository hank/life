#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-embed.h>
#include <stdlib.h>
#define C_BLACK { 0x00, 0x00, 0x00, 0xFF }
#define C_OTHER { 0xCC, 0xAA, 0x00, 0xFF }

static gboolean on_stage_button_clicked(GtkWidget * button, 
    ClutterEvent * event, gpointer data){
  static gboolean already_changed = FALSE;
  ClutterStage * stage = (ClutterStage *)data;
  if(already_changed) {
    ClutterColor stage_color = C_BLACK;
    clutter_stage_set_color(stage, &stage_color);
    g_print("Changed to Black\n");
  } else {
    ClutterColor stage_color = C_OTHER;
    clutter_stage_set_color(stage, &stage_color);
    g_print("Changed to Other\n");
  }

  already_changed = !already_changed;

  return TRUE; /* Stops further event handling */
}

static gboolean on_stage_button_pressed(ClutterStage * stage,
    ClutterEvent * event, gpointer data) {
  gint x = 0;
  gint y = 0;

  clutter_event_get_coords(event, &x, &y);

  g_print("Stage Clicked at %d, %d\n", x, y);
  return TRUE;
}

int main(int argc, char * argv[]) {
  ClutterColor stage_color = C_BLACK; 

  clutter_init(&argc, &argv);
  gtk_init(&argc, &argv);

  /* Create the window and some children */
  GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget * vbox = gtk_vbox_new(FALSE, 6);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show(vbox);

  GtkWidget * button = gtk_button_new_with_label("Change Color");
  gtk_box_pack_end(GTK_BOX(vbox), button, FALSE, FALSE, 0);
  gtk_widget_show(button);

  g_signal_connect(window, "hide", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget * clutter_widget = gtk_clutter_embed_new();
  gtk_box_pack_start(GTK_BOX(vbox), clutter_widget, TRUE, TRUE, 0);
  gtk_widget_show(clutter_widget);

  gtk_widget_set_size_request(clutter_widget, 200, 200);
  ClutterActor * stage = gtk_clutter_embed_get_stage(GTK_CLUTTER_EMBED(clutter_widget));

  clutter_stage_set_color(CLUTTER_STAGE(stage), &stage_color);
  clutter_actor_show(stage);

  /* Connect a signal handler for mouse clicks */
  g_signal_connect(CLUTTER_STAGE(stage), "button-press-event", 
    G_CALLBACK(on_stage_button_pressed), NULL);

  g_signal_connect(button, "button-press-event", 
    G_CALLBACK(on_stage_button_clicked), stage);

  /* Start the main loop */
  gtk_widget_show(GTK_WIDGET(window));
  gtk_main();

  return EXIT_SUCCESS;
}
