#include <gtk/gtk.h>

// `GtkOverlay` allows you to stack widgets on top of each other

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Overlay";
const static gchar* APP_TITLE = "GtkOverlay";

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
  GtkWidget* overlay = gtk_overlay_new();
  GtkWidget* button = gtk_button_new_with_label("Overlay Button");
  GtkWidget* label = gtk_label_new("Overlay Label");

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