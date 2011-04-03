/**
 * file: example.c
 * description: A completely barebone lxpanel plugin doing nothing
 * author: 2noob2banoob
 * based on example_plug by lxde-develloppers
 * GPL v2.0
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib/gi18n.h>

#include <string.h>
#include <lxpanel/plugin.h>

#define EVENT_MOUSE_BUTTON_PRESS_LEFT 1
#define EVENT_MOUSE_BUTTON_PRESS_MIDDLE 2
#define EVENT_MOUSE_BUTTON_PRESS_RIGHT 3

typedef struct {
    Plugin * plugin;
    GtkWidget *main;
    GtkWidget *widget;
    GtkTooltips *tip;
} Example;

gboolean button_press_event( GtkWidget *widget, GdkEventButton* event, Plugin* plugin)
{
    if( event->button == EVENT_MOUSE_BUTTON_PRESS_LEFT )
    {
        
    }
    else if( event->button == EVENT_MOUSE_BUTTON_PRESS_MIDDLE )
    {
        
    }
    else if( event->button == EVENT_MOUSE_BUTTON_PRESS_RIGHT )
    {
        GtkMenu* popup = (GtkMenu*)lxpanel_get_panel_menu( plugin->panel,
                                    plugin, FALSE ); /* lxpanel_menu, can be reimplemented */
        gtk_menu_popup( popup, NULL, NULL, NULL, NULL, event->button, event->time );
        return TRUE;
    }

    RET2(TRUE);
}

static gint update_tooltip(Example *egz)
{
    char *tooltip;
    ENTER;

    tooltip = g_strdup_printf("LXPanel Example plugin");
    gtk_tooltips_set_tip(egz->tip, egz->main, tooltip, NULL);
    g_free(tooltip);

    RET(TRUE);
}

static int example_constructor(Plugin *p, char** fp)
{
    Example *egz;

    /* initialization */
    egz = g_new0(Example, 1);
    egz->plugin = p;
    p->priv = egz;

    p->pwid = gtk_event_box_new(); //you may want to change this to a hbox or vbox if you want to use multiple widgets
    GTK_WIDGET_SET_FLAGS( p->pwid, GTK_NO_WINDOW );
    gtk_container_set_border_width( GTK_CONTAINER(p->pwid), 2 );

    egz->widget = gtk_label_new(" ");
    gtk_container_add(GTK_CONTAINER(p->pwid), egz->widget);

    egz->main = p->pwid;
    egz->tip  = gtk_tooltips_new();
    update_tooltip(egz);

    g_signal_connect (G_OBJECT (p->pwid), "button_press_event", G_CALLBACK (button_press_event), (gpointer) p);
}

static void applyConfig(Plugin* p)
{
    Example *egz = (Example *) p->priv;

    update_tooltip(egz);
}

static void config(Plugin *p, GtkWindow* parent) {
    GtkWidget *dialog;
    Example *egz = (Example *) p->priv;
    dialog = create_generic_config_dlg(_(p->class->name),
            GTK_WIDGET(parent),
            (GSourceFunc) applyConfig, (gpointer) p,
            //_("displayed_varname"), &egz->variable, datatype, //datatype can be CONF_TYPE_STR, CONF_TYPE_INT, CONF_TYPE_BOOL etc.
            NULL);
    gtk_window_present(GTK_WINDOW(dialog));
}

static void example_destructor(Plugin *p)
{
  ENTER;
  Example *egz = (Example *)p->priv;
  g_free(egz);
}

static void save_config( Plugin* p, FILE* fp )
{
    
}

PluginClass example_plugin_class = {

    PLUGINCLASS_VERSIONING,

    type : "example",
    name : N_("Example plugin"),
    version: "0.1",
    description : N_("Example plugin: barebone doing nothing"),

    constructor : example_constructor,
    destructor  : example_destructor,
    config        : config,
    save        : save_config,
    panel_configuration_changed : NULL
};
