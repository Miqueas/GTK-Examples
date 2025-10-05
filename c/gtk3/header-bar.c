#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.HeaderBar";
const static gchar* APP_TITLE = "GtkHeaderBar";
const static gchar* APP_SUBTITLE = "App subtitle";

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
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* header = gtk_header_bar_new();

  gtk_window_set_titlebar(GTK_WINDOW(window), header);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_visible(header, TRUE);
  gtk_header_bar_set_title(GTK_HEADER_BAR(header), APP_TITLE);
  gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header), APP_SUBTITLE);
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
}