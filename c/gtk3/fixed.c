#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Fixed";
const static gchar* APP_TITLE = "GtkFixed";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window, *fixed;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  fixed = gtk_fixed_new();

  gtk_container_add(GTK_CONTAINER(window), fixed);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_fixed_put(GTK_FIXED(fixed), gtk_label_new("A"), 10, 20);
  gtk_fixed_put(GTK_FIXED(fixed), gtk_label_new("B"), 100, 200);
  gtk_fixed_put(GTK_FIXED(fixed), gtk_label_new("C"), 99, 326);
  gtk_widget_show_all(fixed);
}