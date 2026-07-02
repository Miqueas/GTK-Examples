#include <gtk/gtk.h>

static void on_app_startup(GApplication* self, gpointer data);
static void on_app_activate(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Builder";

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
  gchar* src_path = g_path_get_dirname(__FILE__);
  gchar* builder_path = g_build_filename(src_path, "../../data/", "builder-gtk3.ui", NULL);

  GtkBuilder* builder = gtk_builder_new_from_file(builder_path);
  GObject* window = gtk_builder_get_object(builder, "window");
  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(window));

  g_free(src_path);
  g_free(builder_path);
}