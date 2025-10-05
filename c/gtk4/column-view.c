#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_factory_setup(GtkListItemFactory* self, GObject* object, gpointer data);
static void on_factory_bind(GtkListItemFactory* self, GObject* object, gpointer data);

const gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.ColumnView";
const gchar* APP_TITLE = "GtkColumnView";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup),  NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkStringList* list_model = gtk_string_list_new(NULL);
  GtkNoSelection* selection_model = gtk_no_selection_new(G_LIST_MODEL(list_model));
  GtkListItemFactory* key_factory = gtk_signal_list_item_factory_new();
  GtkListItemFactory* value_factory = gtk_signal_list_item_factory_new();
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* scroll = gtk_scrolled_window_new();
  GtkWidget* column_view = gtk_column_view_new(GTK_SELECTION_MODEL(selection_model));
  GtkColumnViewColumn* key_column = gtk_column_view_column_new("Key", key_factory);
  GtkColumnViewColumn* value_column = gtk_column_view_column_new("Value", value_factory);

  for (guint8 i = 0; i < G_MAXUINT8; i++) {
    gtk_string_list_append(list_model, g_strdup_printf("%d", i));
  }

  g_signal_connect(key_factory, "setup", G_CALLBACK(on_factory_setup), NULL);
  g_signal_connect(key_factory, "bind", G_CALLBACK(on_factory_bind), "Key");

  g_signal_connect(value_factory, "setup", G_CALLBACK(on_factory_setup), NULL);
  g_signal_connect(value_factory, "bind", G_CALLBACK(on_factory_bind), "Value");

  gtk_window_set_child(GTK_WINDOW(window), scroll);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), column_view);

  gtk_column_view_set_reorderable(GTK_COLUMN_VIEW(column_view), FALSE);
  gtk_column_view_set_show_row_separators(GTK_COLUMN_VIEW(column_view), TRUE);
  gtk_column_view_set_show_column_separators(GTK_COLUMN_VIEW(column_view), TRUE);
  gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), key_column);
  gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), value_column);

  gtk_column_view_column_set_expand(key_column, TRUE);
  gtk_column_view_column_set_expand(value_column, TRUE);
}

static void on_factory_setup(GtkListItemFactory* self, GObject* object, gpointer data) {
	GtkWidget* label = gtk_label_new("");
  gtk_widget_set_halign(label, GTK_ALIGN_START);
	gtk_list_item_set_child(GTK_LIST_ITEM(object), label);
}

static void on_factory_bind(GtkListItemFactory* self, GObject* object, gpointer data) {
	GtkWidget* label = gtk_list_item_get_child(GTK_LIST_ITEM(object));
	GtkStringObject* string_object = GTK_STRING_OBJECT(gtk_list_item_get_item(GTK_LIST_ITEM(object)));
  const gchar* name = (const gchar*) data;
	const gchar* value = gtk_string_object_get_string(string_object);
  gchar* text = g_strdup_printf("%s: %s", name, value);

	gtk_label_set_label(GTK_LABEL(label), text);
}