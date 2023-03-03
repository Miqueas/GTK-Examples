#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.Fixed";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
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
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", GTK_APPLICATION(self),
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkLabel",
    NULL
  );

  GtkWidget *fixed = g_object_new(GTK_TYPE_FIXED, "visible", TRUE, NULL);

  gtk_fixed_put(GTK_FIXED(fixed), g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "A",
    NULL
  ), 10, 20);

  gtk_fixed_put(GTK_FIXED(fixed), g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "B",
    NULL
  ), 100, 200);

  gtk_fixed_put(GTK_FIXED(fixed), g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "C",
    NULL
  ), 99, 326);

  gtk_container_add(GTK_CONTAINER(win), fixed);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}