#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void on_combo_changed(GtkComboBox *self, gpointer data);

const char *items[8][2] = {
  { "gnome"   , "GNOME" },
  { "plasma"  , "KDE Plasma" },
  { "xfce"    , "XFCE" },
  { "mate"    , "MATE" },
  { "cinnamon", "Cinnamon" },
  { "pantheon", "Pantheon" },
  { "lxde"    , "LXDE" },
  { "lxqt"    , "LXQT" }
};

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK-Examples.Gtk3.ComboBoxText";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

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
  GtkWidget *win, *hint_lbl, *msg_lbl, *combo, *box;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  msg_lbl = gtk_label_new("Select an option");
  combo = g_object_new(GTK_TYPE_COMBO_BOX_TEXT, "visible", TRUE, NULL);
  hint_lbl = gtk_label_new("Default id: gnome");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  GtkWidget *widgets[4] = { msg_lbl, combo, hint_lbl, box };

  for (int i = 0; i < 4; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  for (int i = 0; i < 8; i++)
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), items[i][0], items[i][1]);

  gtk_combo_box_set_active_id(GTK_COMBO_BOX(combo), "gnome");

  g_object_set(box, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);
  gtk_box_pack_start(GTK_BOX(box), msg_lbl, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), combo, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), hint_lbl, FALSE, TRUE, 0);

  g_signal_connect(combo, "changed", G_CALLBACK(on_combo_changed), hint_lbl);
}

void on_combo_changed(GtkComboBox *self, gpointer data) {
  const gchar *id = gtk_combo_box_get_active_id(GTK_COMBO_BOX(self));
  gtk_label_set_label(GTK_LABEL(data), g_strconcat("Option id: ", id, NULL));
}