#include <gtk/gtk.h>

static void on_app_activate(const GApplication* self, gpointer data);
static void on_app_startup(const GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.SpinButton";
const static gchar* APP_TITLE = "GtkSpinButton";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(const GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(const GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* spin_button = gtk_spin_button_new_with_range(0, 100, 10);

  gtk_container_add(GTK_CONTAINER(window), spin_button);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_valign(spin_button, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(spin_button, GTK_ALIGN_CENTER);
  gtk_widget_show(spin_button);
}