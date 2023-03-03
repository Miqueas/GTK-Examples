#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk4.Label";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win, *label;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  label = gtk_label_new("Hi there!");

  gtk_window_set_child(GTK_WINDOW(win), label);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);
}