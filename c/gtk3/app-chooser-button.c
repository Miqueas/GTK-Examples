#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AppChooserButton";
const gchar *appTitle = "GtkAppChooserButton";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

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
  GtkWidget *window, *appChooserButton;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  appChooserButton = gtk_app_chooser_button_new("image/png");

  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_add(GTK_CONTAINER(window), appChooserButton);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_set_visible(appChooserButton, TRUE);
  gtk_widget_set_halign(appChooserButton, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(appChooserButton, GTK_ALIGN_CENTER);
}