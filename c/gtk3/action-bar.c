#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ActionBar";
const gchar *APP_TITLE = "GtkActionBar";

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
  GtkWidget *window, *actionBar, *actionBarLabel, *actionBarButton, *box,
    *boxLabel;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  actionBar = gtk_action_bar_new();
  actionBarLabel = gtk_label_new("Something");
  actionBarButton = gtk_button_new_with_label("A button");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  boxLabel = gtk_label_new("App content");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_action_bar_pack_start(GTK_ACTION_BAR(actionBar), actionBarLabel);
  gtk_action_bar_pack_end(GTK_ACTION_BAR(actionBar), actionBarButton);

  gtk_box_pack_start(GTK_BOX(box), boxLabel, TRUE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(box), actionBar, FALSE, TRUE, 0);
  gtk_widget_show_all(box);
}