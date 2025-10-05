#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_drop_down_notify(GObject* self, GParamSpec* pspec, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.DropDown";
const static gchar* APP_TITLE = "GtkLabel";
const static gchar* ITEMS[9] = {
  "GNOME\0",
  "KDE Plasma\0",
  "XFCE\0",
  "MATE\0",
  "Cinnamon\0",
  "Pantheon\0",
  "LXDE\0",
  "LXQT\0",
  NULL
};

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup), NULL);
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
  GtkStringList* list = gtk_string_list_new(ITEMS);
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* drop_down = gtk_drop_down_new(G_LIST_MODEL(list), NULL);
  GtkWidget* hint_label = gtk_label_new("Select an option");
  GtkWidget* selected_label = gtk_label_new("Selected: None");

  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_append(GTK_BOX(box), hint_label);
  gtk_box_append(GTK_BOX(box), drop_down);
  gtk_box_append(GTK_BOX(box), selected_label);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  g_signal_connect(drop_down, "notify::selected", G_CALLBACK(on_drop_down_notify), selected_label);
}

static void on_drop_down_notify(GObject* self, GParamSpec* pspec, gpointer data) {
  GtkLabel* selected_label = GTK_LABEL(data);
  GtkDropDown* drop_down = GTK_DROP_DOWN(self);
  GtkStringList* list = GTK_STRING_LIST(gtk_drop_down_get_model(drop_down));
  guint selected = gtk_drop_down_get_selected(drop_down);
  const gchar* selected_value = gtk_string_list_get_string(list, selected);
  const gchar* selected_text = g_strconcat("Selected: ", selected_value, NULL);
  g_print("%s\n", selected_text);
  gtk_label_set_label(selected_label, selected_text);
}