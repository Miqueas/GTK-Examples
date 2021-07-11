#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void on_combo_changed(GtkComboBox *self, gpointer data);

char *items[8] = { "GNOME", "KDE Plasma", "XFCE", "MATE", "Cinnamon", "Pantheon", "LXDE", "LXQT" };

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.c-gtk-examples.GtkComboBox",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));

  GtkTreeIter iter;
  GtkListStore *model = gtk_list_store_new(1, G_TYPE_STRING);

  for (int i = 0; i < 8; i++) {
    gtk_list_store_append(model, &iter);
    gtk_list_store_set(model, &iter, 0, items[i], -1);
  }

  GtkWidget *label = g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "Default option: 0",
    NULL
  );

  GtkWidget *combo = g_object_new(
    GTK_TYPE_COMBO_BOX,
    "visible", TRUE,
    "model", model,
    "active", 0,
    NULL
  );

  GtkCellRenderer *render = gtk_cell_renderer_text_new();
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), render, TRUE);
  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), render, "text", 0, NULL);

  GtkWidget *box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "spacing", 10,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  gtk_box_pack_start(
    GTK_BOX(box),
    g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "Select an option", NULL),
    FALSE, TRUE, 0
  );

  gtk_box_pack_start(GTK_BOX(box), combo, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), label, FALSE, TRUE, 0);

  g_signal_connect(combo, "changed", G_CALLBACK(on_combo_changed), label);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "My App",
    "subtitle", "An awesome app that you'll love",
    NULL
  );

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

void on_combo_changed(GtkComboBox *self, gpointer data) {
  int n = gtk_combo_box_get_active(GTK_COMBO_BOX(self));
  char text[128];
  sprintf(text, "Option %d selected (%s)", n, items[n]);
  g_object_set(data, "label", text, NULL);
}