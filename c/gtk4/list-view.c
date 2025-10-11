#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_setup(GtkListItemFactory* self, GObject* item, gpointer data);
static void on_bind(GtkListItemFactory* self, GObject* item, gpointer data);
static void on_activate(GtkListView* self, guint position, gpointer data);

const gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.ListView";
const gchar* APP_TITLE = "GtkListView";

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
  GtkListItemFactory* factory = gtk_signal_list_item_factory_new();

  for (guint8 i = 0; i < G_MAXUINT8; i++) {
    gtk_string_list_append(list_model, g_strdup_printf("Item %d", i));
  }

  g_signal_connect(factory, "setup", G_CALLBACK(on_setup), NULL);
  g_signal_connect(factory, "bind", G_CALLBACK(on_bind), NULL);

  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* scroll = gtk_scrolled_window_new();
  GtkWidget* list_view = gtk_list_view_new(GTK_SELECTION_MODEL(selection_model), factory);

  gtk_window_set_child(GTK_WINDOW(window), scroll);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), list_view);

  g_signal_connect(list_view, "activate", G_CALLBACK(on_activate), NULL);
  gtk_list_view_set_single_click_activate(GTK_LIST_VIEW(list_view), TRUE);
}

static void on_setup(GtkListItemFactory* self, GObject* item, gpointer data) {
  GtkWidget* label = gtk_label_new("");
  gtk_list_item_set_child(GTK_LIST_ITEM(item), label);
}

static void on_bind(GtkListItemFactory* self, GObject* item, gpointer data) {
  GtkWidget* label = gtk_list_item_get_child(GTK_LIST_ITEM(item));
  GtkStringObject* string_object = GTK_STRING_OBJECT(gtk_list_item_get_item(GTK_LIST_ITEM(item)));
  const gchar* text = gtk_string_object_get_string(string_object);
  gtk_label_set_label(GTK_LABEL(label), text);
}

static void on_activate(GtkListView* self, guint position, gpointer data) {
  GtkNoSelection* selection = GTK_NO_SELECTION(gtk_list_view_get_model(self));
  GListModel* model = gtk_no_selection_get_model(selection);
  GtkStringObject* string_object = GTK_STRING_OBJECT(g_list_model_get_item(model, position));
  const gchar* text = gtk_string_object_get_string(string_object);
  g_print("Activated: %s\n", text);
}