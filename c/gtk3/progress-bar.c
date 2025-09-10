#include <gtk/gtk.h>

// `GtkProgressBar` a progress indicator widget, usually for long running
// operations

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
gboolean fillProgressBar(gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ProgressBar";
const gchar *APP_TITLE = "GtkProgressBar";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
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
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget *progressBar = gtk_progress_bar_new();

  gtk_container_add(GTK_CONTAINER(window), progressBar);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(progressBar);
  gtk_widget_set_valign(progressBar, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(progressBar, GTK_ALIGN_CENTER);
  gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressBar), "Processing...");
  gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progressBar), TRUE);

  g_timeout_add(100, fillProgressBar, progressBar);
}

gboolean fillProgressBar(gpointer data) {
  GtkProgressBar *progressBar = GTK_PROGRESS_BAR(data);
  gdouble fraction = gtk_progress_bar_get_fraction(progressBar);
  fraction += 0.01;
  gtk_progress_bar_set_fraction(progressBar, fraction);
  if (fraction >= 1.0) gtk_progress_bar_set_text(progressBar, "Done");
  return fraction < 1.0;
}