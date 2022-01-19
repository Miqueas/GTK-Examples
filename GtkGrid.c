#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.C-GTK3-Examples.GtkGrid",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

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
  GtkWidget *win, *header, *grid;

  win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", GTK_APPLICATION(self),
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkGrid",
    NULL
  );

  grid = g_object_new(
    GTK_TYPE_GRID,
    "visible", TRUE,
    "column-homogeneous", TRUE,
    "row-homogeneous", TRUE,
    "column-spacing", 10,
    "row-spacing", 10,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      char str[20];
      sprintf(str, "Top: %d. Left: %d", i, j);
      gtk_grid_attach(GTK_GRID(grid), g_object_new(
        GTK_TYPE_LABEL,
        "visible", TRUE,
        "label", str,
        NULL
      ), j, i, 1, 1);
    }
  }

  gtk_container_add(GTK_CONTAINER(win), grid);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}