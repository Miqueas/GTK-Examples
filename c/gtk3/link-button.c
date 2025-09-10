#include <gtk/gtk.h>

// `GtkLinkButton` is a button with a hyperlink. It's supposed to open a web
// browser with the specified location when clicked.

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.LinkButton";
const gchar *APP_TITLE = "GtkLinkButton";
const gchar *url = "https://docs.gtk.org";

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
  GtkWidget *linkButton = gtk_link_button_new_with_label(url, "GTK Docs");

  gtk_container_add(GTK_CONTAINER(window), linkButton);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(linkButton);
  gtk_widget_set_valign(linkButton, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(linkButton, GTK_ALIGN_CENTER);
}