#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onButtonToggled(GtkToggleButton *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.CheckButton";
const gchar *APP_TITLE = "GtkCheckButton";

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
  GtkWidget *window, *button;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  button = gtk_check_button_new_with_label("OFF");

  gtk_container_add(GTK_CONTAINER(window), button);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_visible(button, TRUE);
  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), FALSE);
  g_signal_connect(button, "toggled", G_CALLBACK(onButtonToggled), NULL);
}

void onButtonToggled(GtkToggleButton *self, gpointer data) {
  gboolean active = gtk_toggle_button_get_active(self);

  if (active) gtk_button_set_label(GTK_BUTTON(self), "ON");
  else gtk_button_set_label(GTK_BUTTON(self), "OFF");
}