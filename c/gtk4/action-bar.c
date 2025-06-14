#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk4.ActionBar";
const gchar *appTitle = "GtkActionBar";

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
  GtkWidget *window, *actionBar, *actionBarLabel, *actionBarButton, *box, *boxLabel;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  actionBar = gtk_action_bar_new();
  actionBarLabel = gtk_label_new("Something");
  actionBarButton = gtk_button_new_with_label("A button");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  boxLabel = gtk_label_new("App content");

  gtk_widget_set_vexpand(boxLabel, TRUE);
  gtk_widget_set_hexpand(boxLabel, TRUE);

  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_child(GTK_WINDOW(window), box);

  gtk_action_bar_pack_start(GTK_ACTION_BAR(actionBar), actionBarLabel);
  gtk_action_bar_pack_end(GTK_ACTION_BAR(actionBar), actionBarButton);

  gtk_box_prepend(GTK_BOX(box), boxLabel);
  gtk_box_append(GTK_BOX(box), actionBar);
}