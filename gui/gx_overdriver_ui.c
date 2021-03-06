#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "./paintbox.h"
#include "./gtkknob.h"

#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

#include "./gx_overdriver.h"

struct gx_args;

typedef struct {
    LV2UI_Write_Function write;
    LV2UI_Controller     controller;

    GtkWidget* pbox;
    GtkWidget* box;
    GtkWidget* hbox;
    GtkWidget* vbox;
    GtkWidget* logo;
    GtkObject* bp_adj;
    GtkWidget* bypass;
    GtkWidget* bp_box;
    GtkWidget* bp_label;
    struct gx_args *bp_args;
    GtkWidget* vkbox[4];
    GtkObject* adj[4];
    GtkWidget* knob[4];
    GtkWidget* label[4];
    struct gx_args *args[4];
    GtkWidget* window;  /* For optional show interface. */
} gx_overdriverUI;

struct gx_args {
    gx_overdriverUI* ui;
    int port_index;
} ;

static void ref_value_changed(GtkAdjustment *adj, gpointer* args) {

    gx_args * arg = (gx_args*)args;
    gx_overdriverUI* ui = (gx_overdriverUI*)arg->ui;
    int port_index = arg->port_index;
    float value = gtk_adjustment_get_value(adj);
    ui->write(ui->controller, (PortIndex)port_index, sizeof(float), 0,
                                    (void*)&value);
}

static LV2UI_Handle instantiate(const LV2UI_Descriptor*   descriptor,
            const char*               plugin_uri,
            const char*               bundle_path,
            LV2UI_Write_Function      write_function,
            LV2UI_Controller          controller,
            LV2UI_Widget*             widget,
            const LV2_Feature* const* features) {

    gx_overdriverUI* ui = (gx_overdriverUI*)malloc(sizeof(gx_overdriverUI));
    ui->write       = write_function;
    ui->controller  = controller;
    ui->pbox        = NULL;
    ui->box         = NULL;
    ui->hbox        = NULL;
    ui->vbox        = NULL;
    ui->bypass      = NULL;
    ui->bp_box      = NULL;
    ui->bp_label    = NULL;
    ui->window      = NULL;
    for (int i = 0; i<4;i++) {
        ui->vkbox[i]   = NULL;
        ui->knob[i]    = NULL;
        ui->label[i]   = NULL;
    }

    *widget = NULL;

    const char* plug_name = "GxOverdriver" ;
    ui->logo = gtk_label_new(plug_name);
    GdkColor color;
    gdk_color_parse("#666666", &color);
    gtk_widget_modify_fg (ui->logo, GTK_STATE_NORMAL, &color);
    GtkStyle *style = gtk_widget_get_style(ui->logo);
    pango_font_description_set_size(style->font_desc, 24*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->logo, style->font_desc);

    ui->pbox = gx_paint_box_new(GTK_ORIENTATION_VERTICAL,false, 0);
    set_expose_func(GX_OVERDRIVER_PAINT_BOX(ui->pbox),"pedal_expose");
    ui->box = gtk_vbox_new(FALSE, 4);
    ui->hbox = gtk_hbox_new(TRUE, 40);
    gtk_container_set_border_width(GTK_CONTAINER(ui->hbox),25);
    ui->vbox = gtk_vbox_new(TRUE, 0);

    gtk_box_pack_start(GTK_BOX(ui->pbox), ui->box, TRUE, TRUE, 4);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->hbox, TRUE, TRUE, 4);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->vbox, TRUE, TRUE, 100);
    gtk_box_pack_end(GTK_BOX(ui->pbox), ui->logo, FALSE, FALSE, 0);
    gdk_color_parse("#888888", &color);


    ui->bp_adj = gtk_adjustment_new( 0.0, 0.0, 1.0, 1.0, 1.0, 0);
    ui->bypass = gtk_power_switch_new_with_adjustment(GTK_ADJUSTMENT(ui->bp_adj));
    ui->bp_label = gtk_label_new("POWER");
    ui->bp_box = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->bp_label, GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->bp_label);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->bp_label, style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->bp_box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->bp_box), ui->bypass, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->bp_box), ui->bp_label, FALSE, FALSE, 0);
    ui->bp_args = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->bp_args->ui = ui;
    ui->bp_args->port_index = (int)BYPASS;
    g_signal_connect(G_OBJECT(ui->bp_adj), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->bp_args);


    ui->adj[0] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[0] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[0]));
    ui->label[0] = gtk_label_new("BASS");
    ui->vkbox[0] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[0], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[0]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[0], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[0]), ui->knob[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[0]), ui->label[0], FALSE, FALSE, 0);
    ui->args[0] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[0]->ui = ui;
    ui->args[0]->port_index = (int)BASS;
    g_signal_connect(G_OBJECT(ui->adj[0]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[0]);

    ui->adj[1] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[1] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[1]));
    ui->label[1] = gtk_label_new("DRIVE");
    ui->vkbox[1] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[1], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[1]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[1], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox[1], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[1]), ui->knob[1], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[1]), ui->label[1], FALSE, FALSE, 0);
    ui->args[1] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[1]->ui = ui;
    ui->args[1]->port_index = (int)DRIVE;
    g_signal_connect(G_OBJECT(ui->adj[1]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[1]);

    ui->adj[2] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[2] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[2]));
    ui->label[2] = gtk_label_new("TREBLE");
    ui->vkbox[2] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[2], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[2]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[2], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox[2], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[2]), ui->knob[2], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[2]), ui->label[2], FALSE, FALSE, 0);
    ui->args[2] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[2]->ui = ui;
    ui->args[2]->port_index = (int)TREBLE;
    g_signal_connect(G_OBJECT(ui->adj[2]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[2]);

    ui->adj[3] = gtk_adjustment_new( 0.5, 0.0, 1, 0.01, 0.01*10.0, 0);
    ui->knob[3] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[3]));
    ui->label[3] = gtk_label_new("VOLUME");
    ui->vkbox[3] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[3], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[3]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[3], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->vkbox[3], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[3]), ui->knob[3], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[3]), ui->label[3], FALSE, FALSE, 0);
    ui->args[3] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[3]->ui = ui;
    ui->args[3]->port_index = (int)VOLUME;
    g_signal_connect(G_OBJECT(ui->adj[3]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[3]);



    *widget = ui->pbox;

    return ui;
}

static void cleanup(LV2UI_Handle handle) {

    gx_overdriverUI* ui = (gx_overdriverUI*)handle;
    if (GTK_IS_WIDGET(ui->pbox)) {
        for(int i = 0;i<4;i++) {
            if (GTK_IS_WIDGET(ui->knob[i])) {
                gtk_widget_destroy(ui->knob[i]);
            }
            if (GTK_IS_WIDGET(ui->label[i])) {
                gtk_widget_destroy(ui->label[i]);
            }
            if (GTK_IS_WIDGET(ui->vkbox[i])) {
                gtk_widget_destroy(ui->vkbox[i]);
            }
            if (G_IS_OBJECT(ui->adj[i])) {
                g_object_unref(ui->adj[i]);
            }
        }

        if (GTK_IS_WIDGET(ui->bypass)) {
            gtk_widget_destroy(ui->bypass);
        }
        if (G_IS_OBJECT(ui->bp_adj)) {
            g_object_unref(ui->bp_adj);
        }
        if (GTK_IS_WIDGET(ui->bp_label)) {
            gtk_widget_destroy(ui->bp_label);
        }
        if (GTK_IS_WIDGET(ui->bp_box)) {
            gtk_widget_destroy(ui->bp_box);
        }
        if (GTK_IS_WIDGET(ui->vbox)) {
            gtk_widget_destroy(ui->vbox);
        }
        if (GTK_IS_WIDGET(ui->hbox)) {
            gtk_widget_destroy(ui->hbox);
        }
        if (GTK_IS_WIDGET(ui->box)) {
            gtk_widget_destroy(ui->box);
        }
        if (GTK_IS_WIDGET(ui->pbox)) {
            gtk_widget_destroy(ui->pbox);
        }
        if (GTK_IS_WINDOW(ui->window)) {
            gtk_widget_destroy(ui->window);
        }
        if (ui->bp_args) free(ui->bp_args);
        for(int i = 0;i<4;i++) {
            if (ui->args[i] ) free(ui->args[i]);
        }
        free(ui);
    }

}

static void port_event(LV2UI_Handle handle,
                   uint32_t     port_index,
                   uint32_t     buffer_size,
                   uint32_t     format,
                   const void*  buffer) {

    gx_overdriverUI* ui = (gx_overdriverUI*)handle;
    if ( format == 0 ) {
        float *value = (float*)buffer;
        if (port_index == 2) {
            gtk_adjustment_set_value(GTK_ADJUSTMENT(ui->bp_adj), (gdouble) (*value));
        } else {
            gtk_adjustment_set_value(GTK_ADJUSTMENT(ui->adj[port_index-3]), (gdouble) (*value));
        }
    }

}

/* Optional non-embedded UI show interface. */
static int ui_show(LV2UI_Handle handle) {

    gx_overdriverUI* ui = (gx_overdriverUI*)handle;

    int argc = 0;
    gtk_init(&argc, NULL);

    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(ui->window), ui->pbox);
    gtk_widget_show_all(ui->window);
    gtk_window_present(GTK_WINDOW(ui->window));

    return 0;
}

/* Optional non-embedded UI hide interface. */
static int ui_hide(LV2UI_Handle handle) {

    cleanup( handle);
    return 0;

}

/* Idle interface for optional non-embedded UI. */
static int ui_idle(LV2UI_Handle handle) {

    gx_overdriverUI* ui = (gx_overdriverUI*)handle;
    if (ui->window) {
        g_main_context_iteration (NULL, true);
    }
    return 0;

}

static const void* extension_data(const char* uri) {

    static const LV2UI_Show_Interface show = { ui_show, ui_hide };
    static const LV2UI_Idle_Interface idle = { ui_idle };
    if (!strcmp(uri, LV2_UI__showInterface)) {
        return &show;
    } else if (!strcmp(uri, LV2_UI__idleInterface)) {
        return &idle;
    }
    return NULL;

}

static const LV2UI_Descriptor descriptor = {
    GXPLUGIN_UI_URI,
    instantiate,
    cleanup,
    port_event,
    extension_data
};

LV2_SYMBOL_EXPORT 
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) {

    switch (index) {
    case 0:
        return &descriptor;
    default:
        return NULL;
    }

}
