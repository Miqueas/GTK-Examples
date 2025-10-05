#include <gtk/gtk.h>

// `GtkScale` is a slider control used to select a numeric value within a range

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Scale";
const static gchar* APP_TITLE = "GtkScale";

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
  GtkWidget* scale = gtk_scale_new_with_range(
    GTK_ORIENTATION_HORIZONTAL,
    0.0, // Minimum value
    100.0, // Maximum value
    1.0 // Step increment
  );

  gtk_container_add(GTK_CONTAINER(window), scale);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(scale);
  gtk_scale_add_mark(GTK_SCALE(scale), 25.0, GTK_POS_BOTTOM, "25");
  gtk_scale_add_mark(GTK_SCALE(scale), 50.0, GTK_POS_BOTTOM, "50");
  gtk_scale_add_mark(GTK_SCALE(scale), 75.0, GTK_POS_BOTTOM, "75");
  gtk_widget_set_valign(scale, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(scale, GTK_ALIGN_CENTER);
  gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
  gtk_widget_set_size_request(scale, 240, -1);
}