#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_combo_box_changed(GtkComboBox* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ComboBoxText";
const static gchar* APP_TITLE = "GtkComboBoxText";
const static gchar* VALUES[8][2] = {
  { "gnome", "GNOME" },
  { "plasma", "KDE Plasma" },
  { "xfce", "XFCE" },
  { "mate", "MATE" },
  { "cinnamon", "Cinnamon" },
  { "pantheon", "Pantheon" },
  { "lxde", "LXDE" },
  { "lxqt", "LXQT" }
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
  GtkWidget* window, *hintLabel, *comboBox, *box;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  comboBox = gtk_combo_box_text_new();
  hintLabel = gtk_label_new("Default id: gnome");
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_add(GTK_CONTAINER(window), box);

  for (gint i = 0; i < 8; i++) {
    const gchar* id = VALUES[i][0];
    const gchar* text = VALUES[i][1];
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(comboBox), id, text);
  }

  gtk_combo_box_set_active_id(GTK_COMBO_BOX(comboBox), "gnome");

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(box), gtk_label_new("Select an option"), FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), comboBox, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), hintLabel, FALSE, TRUE, 0);
  gtk_widget_show_all(box);

  g_signal_connect(comboBox, "changed", G_CALLBACK(on_combo_box_changed), hintLabel);
}

void on_combo_box_changed(GtkComboBox* self, gpointer data) {
  GtkLabel* label = GTK_LABEL(data);
  const gchar* id = gtk_combo_box_get_active_id(GTK_COMBO_BOX(self));
  const gchar* labelText = g_strconcat("Option id: ", id, NULL);
  gtk_label_set_label(label, labelText);
}