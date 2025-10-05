#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ActionBar";
const static gchar* APP_TITLE = "GtkActionBar";

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
  GtkWidget* action_bar = gtk_action_bar_new();
  GtkWidget* action_bar_label = gtk_label_new("Something");
  GtkWidget* action_bar_button = gtk_button_new_with_label("A button");
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget* box_label = gtk_label_new("App content");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_action_bar_pack_start(GTK_ACTION_BAR(action_bar), action_bar_label);
  gtk_action_bar_pack_end(GTK_ACTION_BAR(action_bar), action_bar_button);

  gtk_box_pack_start(GTK_BOX(box), box_label, TRUE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(box), action_bar, FALSE, TRUE, 0);
  gtk_widget_show_all(box);
}