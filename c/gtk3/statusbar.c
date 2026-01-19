#include "glib-object.h"
#include "glib.h"
#include <gtk/gtk.h>

static void on_app_activate(const GApplication* self, gpointer data);
static void on_app_startup(const GApplication* self, gpointer data);
static void on_button_clicked(const GtkButton* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Statusbar";
const static gchar* APP_TITLE = "GtkStatusbar";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(const GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(const GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* content_label = gtk_label_new("Content section");
  GtkWidget* content_button = gtk_button_new_with_label("Push message");
  GtkWidget* statusbar = gtk_statusbar_new();

  gtk_container_add(GTK_CONTAINER(window), main_box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_pack_start(GTK_BOX(main_box), content_box, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), statusbar, FALSE, FALSE, 0);
  gtk_widget_show_all(main_box);

  gtk_box_pack_start(GTK_BOX(content_box), content_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(content_box), content_button, FALSE, FALSE, 0);
  gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
  gtk_widget_show_all(content_box);

  g_signal_connect(content_button, "clicked", G_CALLBACK(on_button_clicked), statusbar);
}

static void on_button_clicked(const GtkButton* self, gpointer data) {
  GtkStatusbar* statusbar = GTK_STATUSBAR(data);
  guint context_id = gtk_statusbar_get_context_id(statusbar, "info");

  gtk_statusbar_push(statusbar, context_id, "Statusbar message");
}