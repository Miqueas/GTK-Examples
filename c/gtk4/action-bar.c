#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.ActionBar";
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
  GtkWidget* window, *actionBar, *actionBarLabel, *actionBarButton, *box, *boxLabel;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  actionBar = gtk_action_bar_new();
  actionBarLabel = gtk_label_new("Something");
  actionBarButton = gtk_button_new_with_label("A button");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  boxLabel = gtk_label_new("App content");

  gtk_widget_set_vexpand(boxLabel, TRUE);
  gtk_widget_set_hexpand(boxLabel, TRUE);

  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_action_bar_pack_start(GTK_ACTION_BAR(actionBar), actionBarLabel);
  gtk_action_bar_pack_end(GTK_ACTION_BAR(actionBar), actionBarButton);

  gtk_box_prepend(GTK_BOX(box), boxLabel);
  gtk_box_append(GTK_BOX(box), actionBar);
}