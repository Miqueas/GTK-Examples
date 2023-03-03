#include <gtk/gtk.h>

void app_startup(GApplication *self, gpointer data);
void app_activate(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.Builder";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_startup(GApplication *self, gpointer data) {
  GtkBuilder *builder = gtk_builder_new_from_file("Builder.ui");
  GObject *win = gtk_builder_get_object(builder, "Window");

  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(win));
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}