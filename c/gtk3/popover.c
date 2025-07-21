#include <gtk/gtk.h>

// `GtkPopover` is a bubble-like context window, often used for menus

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onClicked(GtkButton *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Popover";
const gchar *appTitle = "GtkPopover";

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
  GtkWidget *button = gtk_button_new_with_label("Open Menu");
  GtkWidget *popover = gtk_popover_new(button);
  GtkWidget *label = gtk_label_new("Popover Menu");

  gtk_container_add(GTK_CONTAINER(window), button);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(button);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  g_signal_connect(button, "clicked", G_CALLBACK(onClicked), popover);

  gtk_container_add(GTK_CONTAINER(popover), label);
  gtk_container_set_border_width(GTK_CONTAINER(popover), 10);

  gtk_widget_show(label);
}

void onClicked(GtkButton *self, gpointer data) {
  gtk_popover_popup(GTK_POPOVER(data));
}