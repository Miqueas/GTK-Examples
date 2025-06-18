#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onButtonClicked(GtkButton *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ButtonBox";
const gchar *appTitle = "GtkButtonBox";

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
  GtkWidget *window, *buttonBox, *button1, *button2, *button3;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  button1 = gtk_button_new_with_label("Button 1");
  button2 = gtk_button_new_with_label("Button 2");
  button3 = gtk_button_new_with_label("Button 3");

  gtk_container_add(GTK_CONTAINER(window), buttonBox);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_set_halign(buttonBox, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(buttonBox, GTK_ALIGN_CENTER);
  gtk_container_add(GTK_CONTAINER(buttonBox), button1);
  gtk_container_add(GTK_CONTAINER(buttonBox), button2);
  gtk_container_add(GTK_CONTAINER(buttonBox), button3);
  gtk_widget_show_all(buttonBox);

  g_signal_connect(button1, "clicked", G_CALLBACK(onButtonClicked), NULL);
  g_signal_connect(button2, "clicked", G_CALLBACK(onButtonClicked), NULL);
  g_signal_connect(button3, "clicked", G_CALLBACK(onButtonClicked), NULL);
}

void onButtonClicked(GtkButton *self, gpointer data) {
  const gchar *label = gtk_button_get_label(self);
  g_print("%s clicked\n", label);
}