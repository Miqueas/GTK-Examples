#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Application";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  g_print("Hello, world!\n");
}

void onAppStartup(GApplication *self, gpointer data) {
  g_print("Initializing the app... Done!\n");
}