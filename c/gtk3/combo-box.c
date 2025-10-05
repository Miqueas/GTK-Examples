#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
void on_combo_box_changed(GtkComboBox* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ComboBox";
const static gchar* APP_TITLE = "GtkComboBox";
const static gchar* ITEMS[8] = {
  "GNOME",
  "KDE Plasma",
  "XFCE",
  "MATE",
  "Cinnamon",
  "Pantheon",
  "LXDE",
  "LXQT"
};

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
  GtkWidget* message_label = gtk_label_new("Select an option");
  GtkWidget* combo_box = gtk_combo_box_new();
  GtkWidget* hint_label = gtk_label_new("Default option: 0");
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkListStore* list_store = gtk_list_store_new(1, G_TYPE_STRING);
  GtkCellRenderer* render = gtk_cell_renderer_text_new();
  GtkTreeIter iter;

  for (gint i = 0; i < 8; i++) {
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, ITEMS[i], -1);
  }

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_combo_box_set_model(GTK_COMBO_BOX(combo_box), GTK_TREE_MODEL(list_store));
  gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo_box), render, TRUE);
  gtk_cell_layout_set_attributes(
    GTK_CELL_LAYOUT(combo_box),
    render,
    "text",
    0,
    NULL
  );
  g_signal_connect(
    combo_box,
    "changed",
    G_CALLBACK(on_combo_box_changed),
    hint_label
  );

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(box), message_label, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), combo_box, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), hint_label, FALSE, TRUE, 0);
  gtk_widget_show_all(box);
}

void on_combo_box_changed(GtkComboBox* self, gpointer data) {
  gint n = gtk_combo_box_get_active(GTK_COMBO_BOX(self));
  gchar text[128];
  sprintf(text, "Option %d selected (%s)", n, ITEMS[n]);
  g_object_set(data, "label", text, NULL);
}