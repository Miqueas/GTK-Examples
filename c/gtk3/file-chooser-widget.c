#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_selection_changed(GtkFileChooser* self, gpointer data);
static void on_show_hidden(GtkFileChooserWidget* self, gpointer data);
static void on_file_activated(GtkFileChooser* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserWidget";
const static gchar* APP_TITLE = "GtkFileChooserWidget";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* widget = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);

  gtk_container_add(GTK_CONTAINER(window), widget);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_show(widget);
  g_signal_connect(widget, "show-hidden", G_CALLBACK(on_show_hidden), NULL);
  g_signal_connect(widget, "file-activated", G_CALLBACK(on_file_activated), window);
  g_signal_connect(widget, "selection-changed", G_CALLBACK(on_selection_changed), NULL);
}

void on_show_hidden(GtkFileChooserWidget* self, gpointer data) {
  gboolean visible = gtk_file_chooser_get_show_hidden(GTK_FILE_CHOOSER(self));
  g_print("Show hidden files: %s\n", visible ? "Yes" : "No");
}

void on_file_activated(GtkFileChooser* self, gpointer data) {
  gchar* filename = gtk_file_chooser_get_filename(self);
  if (filename == NULL) return;
  g_print("File chosen: %s\n", filename);
  g_free(filename);
  gtk_widget_destroy(GTK_WIDGET(data));
}

void on_selection_changed(GtkFileChooser* self, gpointer data) {
  gchar* filename = gtk_file_chooser_get_filename(self);
  if (filename == NULL) return;
  g_print("File selected: %s\n", filename);
  g_free(filename);
}