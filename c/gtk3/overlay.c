#include <gtk/gtk.h>

// `GtkOverlay` allows you to stack widgets on top of each other

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Overlay";
const gchar *APP_TITLE = "GtkOverlay";

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
  GtkWidget *overlay = gtk_overlay_new();
  GtkWidget *button = gtk_button_new_with_label("Overlay Button");
  GtkWidget *label = gtk_label_new("Overlay Label");

  gtk_container_add(GTK_CONTAINER(window), overlay);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);

  gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);

  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), button);
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), label);
  gtk_widget_show_all(overlay);
}