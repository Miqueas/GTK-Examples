#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onButtonClicked(GtkButton *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Frame";
const gchar *appTitle = "GtkFrame";

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
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget *frame = gtk_frame_new(NULL);
  GtkWidget *button = gtk_button_new_with_label("Toggle frame label");

  gtk_container_add(GTK_CONTAINER(window), frame);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_container_add(GTK_CONTAINER(frame), button);
  gtk_widget_show_all(frame);

  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  g_signal_connect(button, "clicked", G_CALLBACK(onButtonClicked), frame);
}

void onButtonClicked(GtkButton *self, gpointer data) {
  GtkFrame *frame = GTK_FRAME(data);
  const gchar *label = gtk_frame_get_label(frame);

  if (label != NULL) gtk_frame_set_label(frame, NULL);
  else gtk_frame_set_label(frame, "This is a frame");
}