#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.HeaderBar";
const gchar *appTitle = "GtkHeaderBar";
const gchar *appSubtitle = "App subtitle";

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
  GtkWidget *window, *header;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  header = gtk_header_bar_new();

  gtk_window_set_titlebar(GTK_WINDOW(window), header);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_visible(header, TRUE);
  gtk_header_bar_set_title(GTK_HEADER_BAR(header), appTitle);
  gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header), appSubtitle);
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
}