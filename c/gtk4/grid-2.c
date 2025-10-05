#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Grid2";
const static gchar* APP_TITLE = "GtkGrid";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup),  NULL);
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
  GtkWidget* window, *grid;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  grid = gtk_grid_new();

  gtk_window_set_child(GTK_WINDOW(window), grid);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 0. Left: 0"), 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 0. Left: 1"), 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 0. Left: 2"), 2, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 1. Left: 0"), 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 1. Left: 1"), 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 1. Left: 2"), 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 2. Left: 0"), 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 2. Left: 1"), 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Top: 2. Left: 2"), 2, 2, 1, 1);
}