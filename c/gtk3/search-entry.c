#include "glib-object.h"
#include "glib.h"
#include <gtk/gtk.h>

static void on_app_activate(const GApplication* self, gpointer data);
static void on_app_startup(const GApplication* self, gpointer data);
static void on_search_changed(const GtkSearchEntry* self, gpointer data);
static gboolean tree_model_filter_func(GtkTreeModel* self, GtkTreeIter* iter, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.SearchEntry";
const static gchar* APP_TITLE = "GtkSearchEntry";
const static gchar* ITEMS[7] = { "GNOME", "Linux", "C", "GTK 3", "Examples", "Hello", "World", };

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(const GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(const GApplication* self, gpointer data) {
  GtkListStore* list_store = gtk_list_store_new(1, G_TYPE_STRING);
  GtkTreeModel* list_store_filter = gtk_tree_model_filter_new(GTK_TREE_MODEL(list_store), NULL);
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget* search_entry = gtk_search_entry_new();
  GtkWidget* list_view = gtk_tree_view_new();
  GtkCellRenderer* text_renderer_cell = gtk_cell_renderer_text_new();

  for (int i = 0; i < 7; i++) {
    gtk_list_store_insert_with_values(list_store, NULL, -1, 0, ITEMS[i], -1);
  }

  gtk_tree_model_filter_set_visible_func(
    GTK_TREE_MODEL_FILTER(list_store_filter),
    tree_model_filter_func,
    search_entry,
    NULL
  );

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_pack_start(GTK_BOX(box), search_entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), list_view, TRUE, TRUE, 0);
  gtk_widget_show_all(box);

  g_signal_connect(search_entry, "search-changed", G_CALLBACK(on_search_changed), list_store_filter);
  gtk_widget_set_valign(search_entry, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(search_entry, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_top(search_entry, 10);
  gtk_widget_set_margin_end(search_entry, 10);
  gtk_widget_set_margin_start(search_entry, 10);
  gtk_widget_set_margin_bottom(search_entry, 10);

  gtk_tree_view_insert_column_with_attributes(
    GTK_TREE_VIEW(list_view),
    -1,
    "Data",
    text_renderer_cell,
    "text", 0,
    NULL
  );
  gtk_tree_view_set_model(GTK_TREE_VIEW(list_view), GTK_TREE_MODEL(list_store_filter));
  gtk_widget_show_all(list_view);
}

static void on_search_changed(const GtkSearchEntry* self, gpointer data) {
  GtkTreeModelFilter* list_store_filter = GTK_TREE_MODEL_FILTER(data);
  gtk_tree_model_filter_refilter(list_store_filter);
}

static gboolean tree_model_filter_func(GtkTreeModel* self, GtkTreeIter* iter, gpointer data) {
  const gchar* search_entry_query = gtk_entry_get_text(GTK_ENTRY(data));
  glong str_len = g_utf8_strlen(search_entry_query, -1);

  if (str_len == 0) return TRUE;

  GRegex* regex = g_regex_new(search_entry_query, G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT, NULL);
  gchar* value;

  gtk_tree_model_get(self, iter, 0, &value, -1);

  gboolean has_match = g_regex_match(regex, value, G_REGEX_MATCH_DEFAULT, NULL);

  g_free(value);
  return has_match;
}