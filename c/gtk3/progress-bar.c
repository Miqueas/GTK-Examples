#include <gtk/gtk.h>

// `GtkProgressBar` a progress indicator widget, usually for long running
// operations

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
gboolean fill_progress_bar(gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ProgressBar";
const static gchar* APP_TITLE = "GtkProgressBar";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);
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
  GtkWidget* progress_bar = gtk_progress_bar_new();

  gtk_container_add(GTK_CONTAINER(window), progress_bar);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(progress_bar);
  gtk_widget_set_valign(progress_bar, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(progress_bar, GTK_ALIGN_CENTER);
  gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "Processing...");
  gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), TRUE);

  g_timeout_add(100, fill_progress_bar, progress_bar);
}

gboolean fill_progress_bar(gpointer data) {
  GtkProgressBar* progress_bar = GTK_PROGRESS_BAR(data);
  gdouble fraction = gtk_progress_bar_get_fraction(progress_bar);
  fraction += 0.01;
  gtk_progress_bar_set_fraction(progress_bar, fraction);
  if (fraction >= 1.0) gtk_progress_bar_set_text(progress_bar, "Done");
  return fraction < 1.0;
}