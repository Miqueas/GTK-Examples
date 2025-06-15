#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Fixed";
const gchar *appTitle = "GtkFixed";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *fixed;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  fixed = gtk_fixed_new();

  gtk_window_set_child(GTK_WINDOW(window), fixed);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_fixed_put(GTK_FIXED(fixed), gtk_label_new("A"), 10, 20);
  gtk_fixed_put(GTK_FIXED(fixed), gtk_label_new("B"), 100, 200);
  gtk_fixed_put(GTK_FIXED(fixed), gtk_label_new("C"), 99, 326);
}