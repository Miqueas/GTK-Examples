#include <gtk/gtk.h>

// `GtkScaleButton` is a button that pops up a scale control

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
void on_value_changed(GtkScaleButton* self, gdouble value, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ScaleButton";
const static gchar* APP_TITLE = "GtkScaleButton";
const static gchar* ICONS[2] = { "zoom-out", "zoom-in" };

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
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* button = gtk_scale_button_new(
    GTK_ICON_SIZE_SMALL_TOOLBAR, // Icon size
    0.0, // Minimum value
    100.0, // Maximum value
    1.0, // Step increment
    ICONS
  );

  gtk_container_add(GTK_CONTAINER(window), button);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(button);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  g_signal_connect(button, "value-changed", G_CALLBACK(on_value_changed), NULL);
}

void on_value_changed(GtkScaleButton* self, gdouble value, gpointer data) {
  g_print("Scale value: %f\n", value);
}