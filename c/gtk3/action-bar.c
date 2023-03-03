#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.ActionBar";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win, *bar, *bar_lbl, *bar_btn, *box, *box_lbl;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  bar = gtk_action_bar_new();
  bar_lbl = gtk_label_new("Something");
  bar_btn = gtk_button_new_with_label("A button");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  box_lbl = gtk_label_new("App content");

  GtkWidget *widgets[5] = { bar, bar_lbl, bar_btn, box, box_lbl };

  for (int i = 0; i < 5; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  gtk_action_bar_pack_start(GTK_ACTION_BAR(bar), bar_lbl);
  gtk_action_bar_pack_end(GTK_ACTION_BAR(bar), bar_btn);

  gtk_box_pack_start(GTK_BOX(box), box_lbl, TRUE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(box), bar, FALSE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(win), box);
}