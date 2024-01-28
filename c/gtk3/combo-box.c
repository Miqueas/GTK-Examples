#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onComboBoxChanged(GtkComboBox *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ComboBox";
const gchar *appTitle = "GtkComboBox";
const char *items[8] = {
  "GNOME",
  "KDE Plasma",
  "XFCE",
  "MATE",
  "Cinnamon",
  "Pantheon",
  "LXDE",
  "LXQT"
};

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
  GtkWidget *window, *messageLabel, *hintLabel, *comboBox, *box;
  GtkCellRenderer *render;
  GtkListStore *model;
  GtkTreeIter iter;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  messageLabel = gtk_label_new("Select an option");
  comboBox = gtk_combo_box_new();
  hintLabel = gtk_label_new("Default option: 0");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  model = gtk_list_store_new(1, G_TYPE_STRING);
  render = gtk_cell_renderer_text_new();

  for (int i = 0; i < 8; i++) {
    gtk_list_store_append(model, &iter);
    gtk_list_store_set(model, &iter, 0, items[i], -1);
  }

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_combo_box_set_model(GTK_COMBO_BOX(comboBox), GTK_TREE_MODEL(model));
  gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox), 0);
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(comboBox), render, TRUE);
  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(comboBox), render, "text", 0, NULL);
  g_signal_connect(comboBox, "changed", G_CALLBACK(onComboBoxChanged), hintLabel);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(box), messageLabel, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), comboBox, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), hintLabel, FALSE, TRUE, 0);
  gtk_widget_show_all(box);
}

void onComboBoxChanged(GtkComboBox *self, gpointer data) {
  int n = gtk_combo_box_get_active(GTK_COMBO_BOX(self));
  char text[128];
  sprintf(text, "Option %d selected (%s)", n, items[n]);
  g_object_set(data, "label", text, NULL);
}