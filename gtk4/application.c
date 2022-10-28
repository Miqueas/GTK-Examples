#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK-Examples.Gtk4.Application";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  g_print("Hello there!\n");
}

void app_startup(GApplication *self, gpointer data) {
  g_print("Initializing the app... Done!\n");
}