#include <gtk/gtk.h>

void app_startup(GApplication *self, gpointer data) {
  GtkBuilder *builder = g_object_new(GTK_TYPE_BUILDER, NULL);
  gtk_builder_add_from_file(builder, "GtkBuilder.ui", NULL);

  GObject *win = gtk_builder_get_object(builder, "Window");

  gtk_application_add_window(
    GTK_APPLICATION(self),
    GTK_WINDOW(win)
  );
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.c-gtk-examples.GtkBuilder",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}