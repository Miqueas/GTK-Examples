#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void on_combo_changed(GtkComboBox *self, gpointer data);

const char *items[8] = { "GNOME", "KDE Plasma", "XFCE", "MATE", "Cinnamon", "Pantheon", "LXDE", "LXQT" };

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.ComboBox";
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
  GtkWidget *win, *msg_lbl, *hint_lbl, *combo, *box;
  GtkCellRenderer *render;
  GtkListStore *model;
  GtkTreeIter iter;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  msg_lbl = gtk_label_new("Select an option");
  combo = gtk_combo_box_new();
  hint_lbl = gtk_label_new("Default option: 0");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  model = gtk_list_store_new(1, G_TYPE_STRING);
  render = gtk_cell_renderer_text_new();
  
  gtk_widget_set_visible(msg_lbl, TRUE);
  gtk_widget_set_visible(combo, TRUE);
  gtk_widget_set_visible(hint_lbl, TRUE);
  gtk_widget_set_visible(box, TRUE);

  for (int i = 0; i < 8; i++) {
    gtk_list_store_append(model, &iter);
    gtk_list_store_set(model, &iter, 0, items[i], -1);
  }

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  gtk_combo_box_set_model(GTK_COMBO_BOX(combo), GTK_TREE_MODEL(model));
  gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), render, TRUE);
  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), render, "text", 0, NULL);
  g_signal_connect(combo, "changed", G_CALLBACK(on_combo_changed), hint_lbl);

  g_object_set(box, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);
  gtk_box_pack_start(GTK_BOX(box), msg_lbl, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), combo, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), hint_lbl, FALSE, TRUE, 0);
}

void on_combo_changed(GtkComboBox *self, gpointer data) {
  int n = gtk_combo_box_get_active(GTK_COMBO_BOX(self));
  char text[128];
  sprintf(text, "Option %d selected (%s)", n, items[n]);
  g_object_set(data, "label", text, NULL);
}