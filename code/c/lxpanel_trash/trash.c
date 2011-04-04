/**
 * file: trash.c
 * description: Trash plugin for lxpanel
 * author: Erik Gregg
 * based on example by 2noob2banoob
 * GPL v2.0
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include <string.h>
#include <lxpanel/plugin.h>

// Icon
#include "trash.xpm"
#include "trash_full.xpm"

#define EVENT_MOUSE_BUTTON_PRESS_LEFT 1
#define EVENT_MOUSE_BUTTON_PRESS_MIDDLE 2
#define EVENT_MOUSE_BUTTON_PRESS_RIGHT 3

typedef struct {
    Plugin*      plugin;
    GtkWidget*   main;
    GtkWidget*   widget;
    GdkPixbuf*   trash_icon;
    GtkWidget*   trash_image;
    GdkPixbuf*   trash_full_icon;
    GtkWidget*   trash_full_image;
    GtkTooltips* tip;
    uint8_t      currently_full;
} Trash;

static gint update_tooltip(Trash *);

static void empty_trash(gchar* v_trash)
{
    Trash* trash = (Trash*)v_trash;
    //Plugin* p = trash->plugin;
    FILE* fpipe = NULL;
    char* command = "empty-trash";
    if(!(fpipe = (FILE*)popen(command, "r")))
    {
        return;
    }
    pclose(fpipe);
    // Update trash icon, emit sound?
    update_tooltip(trash);
}

static void open_trash(gchar* v_trash)
{
    //Trash* trash = (Trash*)v_trash;
    //Plugin* p = trash->plugin;
}

gboolean mouseover_event( GtkWidget *widget, GdkEventButton* event, Plugin* plugin)
{
    Trash* trash = (Trash*)plugin->priv;
    // Simply update the tooltip
    update_tooltip(trash);
    // Indicate it should be handled upstream.
    RET2(FALSE);
}

gboolean button_press_event( GtkWidget *widget, GdkEventButton* event, Plugin* plugin)
{
    GtkMenu* popup = NULL;
    GtkWidget* empty_item = NULL;
    GtkWidget* open_item = NULL;
    Trash* trash = (Trash*)plugin->priv;
    update_tooltip(trash);
    switch(event->button)
    {
        case EVENT_MOUSE_BUTTON_PRESS_LEFT:
            popup = gtk_menu_new(); 
            open_item = gtk_menu_item_new_with_label("Open");
            empty_item = gtk_menu_item_new_with_label("Empty");
            gtk_menu_append(GTK_MENU(popup), empty_item);
            gtk_menu_append(GTK_MENU(popup), open_item);

            gtk_signal_connect_object (GTK_OBJECT (open_item), "activate",
                GTK_SIGNAL_FUNC (open_trash), (gpointer)trash);
            gtk_signal_connect_object (GTK_OBJECT (empty_item), "activate",
                GTK_SIGNAL_FUNC (empty_trash), (gpointer)trash);

            gtk_widget_show(empty_item);
            gtk_widget_show(open_item);
            gtk_menu_popup( popup, NULL, NULL, NULL, NULL, event->button, event->time );
            break;
        case EVENT_MOUSE_BUTTON_PRESS_MIDDLE:
            break;
        case EVENT_MOUSE_BUTTON_PRESS_RIGHT:
            popup = (GtkMenu*)lxpanel_get_panel_menu( plugin->panel,
                    plugin, FALSE ); /* lxpanel_menu, can be reimplemented */
            gtk_menu_popup( popup, NULL, NULL, NULL, NULL, event->button, event->time );
            return TRUE;
            break;
        default:
            break;
    }

    RET2(TRUE);
}

static gint update_tooltip(Trash *trash)
{
    Plugin* p = trash->plugin;
    char *tooltip;
    ENTER;

    uint32_t i = 0;
    FILE* fpipe = NULL;
    char* command = "list-trash";
    char line[1024] = {0};
    if(!(fpipe = (FILE*)popen(command, "r")))
    {
        RET(0);
    }
    // Find how many files are in the trash.
    while( fgets(line, sizeof(line), fpipe) )
    {
        ++i;
    }
    pclose(fpipe);
    if(i>0) { // Trash is 'full'
        tooltip = g_strdup_printf("Trash: %i files", i);
        if(!trash->currently_full) {
            gtk_container_remove(GTK_CONTAINER(p->pwid), trash->trash_image);
            trash->currently_full = 1;
        }
        gtk_container_add (GTK_CONTAINER(p->pwid), trash->trash_full_image);
        gtk_widget_show(trash->trash_full_image);
    } else { // Trash is empty
        tooltip = g_strdup_printf("Trash: Empty");
        if(trash->currently_full) {
            gtk_container_remove(GTK_CONTAINER(p->pwid), trash->trash_full_image);
            trash->currently_full = 0;
        }
        gtk_container_add (GTK_CONTAINER(p->pwid), trash->trash_image);
        gtk_widget_show(trash->trash_image);
    }
    gtk_tooltips_set_tip(trash->tip, trash->main, tooltip, NULL);
    g_free(tooltip);

    RET(TRUE);
}

static int trash_constructor(Plugin *p, char** fp)
{
    Trash *trash;

    /* initialization */
    trash = g_new0(Trash, 1);
    trash->plugin = p;
    p->priv = trash;

    p->pwid = gtk_event_box_new(); //you may want to change this to a hbox or vbox if you want to use multiple widgets
    GTK_WIDGET_SET_FLAGS( p->pwid, GTK_NO_WINDOW );
    gtk_container_set_border_width( GTK_CONTAINER(p->pwid), 2 );

    gtk_widget_set_size_request(trash->main, p->panel->icon_size, p->panel->icon_size);

    trash->main = p->pwid;
    trash->tip  = gtk_tooltips_new();
    update_tooltip(trash);

    g_signal_connect (G_OBJECT (p->pwid), "button_press_event", G_CALLBACK (button_press_event), (gpointer) p);
    // Mouse-over
    g_signal_connect (G_OBJECT (p->pwid), "enter", G_CALLBACK (mouseover_event), (gpointer) p);

    // Icons
    trash->trash_icon = gdk_pixbuf_new_from_xpm_data((const char **)trashcan_xpm);
    if (trash->trash_icon) {
        trash->trash_image = gtk_image_new_from_pixbuf(trash->trash_icon);
        // Ref it so it's not deleted
        g_object_ref(trash->trash_image);
        // Add the empty one to the container as an initial case.
        gtk_container_add (GTK_CONTAINER(p->pwid), trash->trash_full_image);
    }
    else RET(0);
    trash->trash_full_icon = gdk_pixbuf_new_from_xpm_data((const char **)trash_full_xpm);
    if (trash->trash_full_icon) {
        trash->trash_full_image = gtk_image_new_from_pixbuf(trash->trash_full_icon);
        // Ref it so it's not deleted
        g_object_ref(trash->trash_image);
    }
    else RET(0);
    // Update trash status
    update_tooltip(trash);
    gtk_widget_show_all(p->pwid);

    RET(TRUE);
}

static void applyConfig(Plugin* p)
{
    Trash *trash = (Trash *) p->priv;

    update_tooltip(trash);
}

static void config(Plugin *p, GtkWindow* parent) {
    GtkWidget *dialog;
    //Trash *trash = (Trash *) p->priv;
    dialog = create_generic_config_dlg(_(p->class->name),
            GTK_WIDGET(parent),
            (GSourceFunc) applyConfig, (gpointer) p,
            //_("displayed_varname"), &trash->variable, datatype, //datatype can be CONF_TYPE_STR, CONF_TYPE_INT, CONF_TYPE_BOOL etc.
            NULL);
    gtk_window_present(GTK_WINDOW(dialog));
}

static void trash_destructor(Plugin *p)
{
  ENTER;
  Trash *trash = (Trash *)p->priv;
  if (trash->trash_icon)
      g_object_unref(trash->trash_icon);
  if (trash->trash_image)
      g_object_unref(trash->trash_image);
  if (trash->trash_full_icon)
      g_object_unref(trash->trash_full_icon);
  if (trash->trash_full_image)
      g_object_unref(trash->trash_full_image);
  g_free(trash);
}

static void save_config( Plugin* p, FILE* fp )
{
    
}

PluginClass trash_plugin_class = {

    PLUGINCLASS_VERSIONING,

    type : "trash",
    name : N_("Trash plugin"),
    version: "0.1",
    description : N_("Trash plugin: accesses the trash"),

    constructor : trash_constructor,
    destructor  : trash_destructor,
    config        : config,
    save        : save_config,
    panel_configuration_changed : NULL
};
