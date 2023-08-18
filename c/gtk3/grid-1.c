#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Grid1";
const gchar *appTitle = "GtkGrid";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *grid;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  grid = gtk_grid_new();

  gtk_container_add(GTK_CONTAINER(window), grid);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      char str[20];
      sprintf(str, "Top: %d. Left: %d", i, j);
      gtk_grid_attach(GTK_GRID(grid), gtk_label_new(str), j, i, 1, 1);
    }
  }

  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_widget_show_all(grid);
}