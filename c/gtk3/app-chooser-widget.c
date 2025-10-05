#include <gtk/gtk.h>

typedef enum {
  SHOW_ALL,
  SHOW_DEFAULT,
  SHOW_FALLBACK,
  SHOW_OTHER,
  SHOW_RECOMMENDED
} AppChooserWidgetSetting;

typedef struct _ToggleButtonData {
  GPtrArray* widgets;
  AppChooserWidgetSetting setting;
} ToggleButtonData;

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_app_shutdown(GApplication* self, gpointer data);
static void on_button_toggled(GtkToggleButton* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AppChooserWidget";
const static gchar* APP_TITLE = "GtkAppChooserWidget";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GPtrArray* widgets = g_ptr_array_sized_new(6);
  ToggleButtonData* show_all_data = g_new(ToggleButtonData, 1);
  ToggleButtonData* show_default_data = g_new(ToggleButtonData, 1);
  ToggleButtonData* show_fallback_data = g_new(ToggleButtonData, 1);
  ToggleButtonData* show_other_data = g_new(ToggleButtonData, 1);
  ToggleButtonData* show_recommended_data = g_new(ToggleButtonData, 1);
  GPtrArray* free_data = g_ptr_array_sized_new(6);
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* app_chooser_widget = gtk_app_chooser_widget_new("image/png");
  GtkWidget* settings_label = gtk_label_new("Settings:");
  GtkWidget* show_all_toggle = gtk_check_button_new_with_label("Show all applications");
  GtkWidget* show_default_toggle = gtk_check_button_new_with_label("Show default");
  GtkWidget* show_fallback_toggle = gtk_check_button_new_with_label("Show fallback");
  GtkWidget* show_other_toggle = gtk_check_button_new_with_label("Show other");
  GtkWidget* show_recommended_toggle = gtk_check_button_new_with_label("Show recommended");

  g_ptr_array_add(widgets, app_chooser_widget);
  g_ptr_array_add(widgets, show_all_toggle);
  g_ptr_array_add(widgets, show_default_toggle);
  g_ptr_array_add(widgets, show_fallback_toggle);
  g_ptr_array_add(widgets, show_other_toggle);
  g_ptr_array_add(widgets, show_recommended_toggle);

  show_all_data->widgets = widgets;
  show_all_data->setting = SHOW_ALL;
  show_default_data->widgets = widgets;
  show_default_data->setting = SHOW_DEFAULT;
  show_fallback_data->widgets = widgets;
  show_fallback_data->setting = SHOW_FALLBACK;
  show_other_data->widgets = widgets;
  show_other_data->setting = SHOW_OTHER;
  show_recommended_data->widgets = widgets;
  show_recommended_data->setting = SHOW_RECOMMENDED;

  g_ptr_array_add(free_data, widgets);
  g_ptr_array_add(free_data, show_all_data);
  g_ptr_array_add(free_data, show_default_data);
  g_ptr_array_add(free_data, show_fallback_data);
  g_ptr_array_add(free_data, show_other_data);
  g_ptr_array_add(free_data, show_recommended_data);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), app_chooser_widget, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), settings_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), show_all_toggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), show_default_toggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), show_fallback_toggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), show_other_toggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), show_recommended_toggle, FALSE, FALSE, 0);
  gtk_widget_show_all(box);

  gtk_widget_set_halign(settings_label, GTK_ALIGN_START);

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(show_all_toggle),
    gtk_app_chooser_widget_get_show_all(
      GTK_APP_CHOOSER_WIDGET(app_chooser_widget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(show_default_toggle),
    gtk_app_chooser_widget_get_show_default(
      GTK_APP_CHOOSER_WIDGET(app_chooser_widget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(show_fallback_toggle),
    gtk_app_chooser_widget_get_show_fallback(
      GTK_APP_CHOOSER_WIDGET(app_chooser_widget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(show_other_toggle),
    gtk_app_chooser_widget_get_show_other(
      GTK_APP_CHOOSER_WIDGET(app_chooser_widget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(show_recommended_toggle),
    gtk_app_chooser_widget_get_show_recommended(
      GTK_APP_CHOOSER_WIDGET(app_chooser_widget)
    )
  );

  g_signal_connect(
    show_all_toggle,
    "toggled",
    G_CALLBACK(on_button_toggled),
    show_all_data
  );

  g_signal_connect(
    show_default_toggle,
    "toggled",
    G_CALLBACK(on_button_toggled),
    show_default_data
  );

  g_signal_connect(
    show_fallback_toggle,
    "toggled",
    G_CALLBACK(on_button_toggled),
    show_fallback_data
  );

  g_signal_connect(
    show_other_toggle,
    "toggled",
    G_CALLBACK(on_button_toggled),
    show_other_data
  );

  g_signal_connect(
    show_recommended_toggle,
    "toggled",
    G_CALLBACK(on_button_toggled),
    show_recommended_data
  );

  g_signal_connect(
    self,
    "shutdown",
    G_CALLBACK(on_app_shutdown),
    free_data
  );
}

static void on_app_shutdown(GApplication* self, gpointer data) {
  GPtrArray* free_data = (GPtrArray*) data;
  GPtrArray* widgets = (GPtrArray*) free_data->pdata[0];
  ToggleButtonData* show_all_data = (ToggleButtonData*) free_data->pdata[1];
  ToggleButtonData* show_default_data = (ToggleButtonData*) free_data->pdata[2];
  ToggleButtonData* show_fallback_data = (ToggleButtonData*) free_data->pdata[3];
  ToggleButtonData* show_other_data = (ToggleButtonData*) free_data->pdata[4];
  ToggleButtonData* show_recommended_data = (ToggleButtonData*) free_data->pdata[5];

  g_free(show_all_data);
  g_free(show_default_data);
  g_free(show_fallback_data);
  g_free(show_other_data);
  g_free(show_recommended_data);
  g_ptr_array_free(widgets, TRUE);
  g_ptr_array_free(free_data, TRUE);

  free_data = NULL;
  widgets = NULL;
  show_all_data = NULL;
  show_default_data = NULL;
  show_fallback_data = NULL;
  show_other_data = NULL;
  show_recommended_data = NULL;
}

static void on_button_toggled(GtkToggleButton* self, gpointer data) {
  ToggleButtonData* _data = (ToggleButtonData*) data; 
  GPtrArray* widgets = _data->widgets;
  AppChooserWidgetSetting setting = _data->setting;
  GtkAppChooserWidget* app_chooser_widget = GTK_APP_CHOOSER_WIDGET(widgets->pdata[0]);
  GtkToggleButton* show_all_toggle = GTK_TOGGLE_BUTTON(widgets->pdata[1]);
  gboolean show_all = gtk_toggle_button_get_active(show_all_toggle);
  gboolean is_active = gtk_toggle_button_get_active(self);

  switch (setting) {
    case SHOW_ALL:
      gtk_app_chooser_widget_set_show_all(app_chooser_widget, is_active);
      if (is_active) {
        for (guint i = 2; i < widgets->len; i++) {
          GtkToggleButton* toggle = GTK_TOGGLE_BUTTON(widgets->pdata[i]);
          gtk_toggle_button_set_active(toggle, FALSE);
        }
      }
      break;
    case SHOW_DEFAULT:
      gtk_app_chooser_widget_set_show_default(app_chooser_widget, is_active);
      if (show_all && is_active) gtk_toggle_button_set_active(show_all_toggle, FALSE);
      break;
    case SHOW_FALLBACK:
      gtk_app_chooser_widget_set_show_fallback(app_chooser_widget, is_active);
      if (show_all && is_active) gtk_toggle_button_set_active(show_all_toggle, FALSE);
      break;
    case SHOW_OTHER:
      gtk_app_chooser_widget_set_show_other(app_chooser_widget, is_active);
      if (show_all && is_active) gtk_toggle_button_set_active(show_all_toggle, FALSE);
      break;
    case SHOW_RECOMMENDED:
      gtk_app_chooser_widget_set_show_recommended(app_chooser_widget, is_active);
      if (show_all && is_active) gtk_toggle_button_set_active(show_all_toggle, FALSE);
      break;
    default: break;
  }
}