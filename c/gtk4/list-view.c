#include "list-view.h"

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static GListStore* create_store(void);
static void on_setup(GtkListItemFactory* self, GObject* item, gpointer data);
static void on_bind(GtkListItemFactory* self, GObject* item, gpointer data);
static void on_activate(GtkListView* self, guint position, gpointer data);

int
main(int argc,
     char** argv)
{
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup),  NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void
on_app_activate(GApplication* self,
                gpointer data)
{
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

static void
on_app_startup(GApplication* self,
               gpointer data)
{
  GListStore* model = create_store();
  GtkNoSelection* selection_model = gtk_no_selection_new(G_LIST_MODEL(model));
  GtkListItemFactory* factory = gtk_signal_list_item_factory_new();
  g_signal_connect(factory, "setup", G_CALLBACK(on_setup), NULL);
  g_signal_connect(factory, "bind", G_CALLBACK(on_bind), NULL);

  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* scroll = gtk_scrolled_window_new();
  GtkWidget* list_view = gtk_list_view_new(
    GTK_SELECTION_MODEL(selection_model),
    factory
  );

  gtk_window_set_child(GTK_WINDOW(window), scroll);
  gtk_window_set_title(GTK_WINDOW(window), APP_NAME);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), list_view);

  g_signal_connect(list_view, "activate", G_CALLBACK(on_activate), NULL);
}

static GListStore*
create_store(void)
{
  GListStore* store = g_list_store_new(MGE_TYPE_ITEM);

  for (guint8 i = 0; i < G_MAXUINT8; i++) {
    gchar* key = g_strdup_printf("Key %d", i);
    gchar* value = g_strdup_printf("Value %d", i);
    MgeItem* item = mge_item_new(key, value);
    g_list_store_append(store, item);
    g_object_unref(item);
    g_free(key);
    g_free(value);
  }

  return store;
}

static void
on_setup(GtkListItemFactory* self,
         GObject* item,
         gpointer data)
{
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget* keyLabel = gtk_label_new("Key");
  GtkWidget* valueLabel = gtk_label_new("Value");

  gtk_box_append(GTK_BOX(box), keyLabel);
  gtk_box_append(GTK_BOX(box), valueLabel);
  gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
  gtk_list_item_set_child(GTK_LIST_ITEM(item), box);
}

static void
on_bind(GtkListItemFactory* self,
        GObject* item,
        gpointer data)
{
  GtkWidget* box = gtk_list_item_get_child(GTK_LIST_ITEM(item));
  GtkWidget* keyLabel = gtk_widget_get_first_child(box);
  GtkWidget* valueLabel = gtk_widget_get_last_child(box);
  MgeItem* mge_item = MGE_ITEM(gtk_list_item_get_item(GTK_LIST_ITEM(item)));

  gtk_label_set_label(GTK_LABEL(keyLabel), mge_item->key);
  gtk_label_set_label(GTK_LABEL(valueLabel), mge_item->value);
}

static void
on_activate(GtkListView* self,
            guint position,
            gpointer data)
{
  GtkNoSelection* selection = GTK_NO_SELECTION(gtk_list_view_get_model(self));
  GListModel* model = gtk_no_selection_get_model(selection);
  MgeItem* mge_item = MGE_ITEM(g_list_model_get_item(model, position));

  g_print(
    "Activated item at position %d: %s - %s\n",
    position,
    mge_item->key,
    mge_item->value
  );

  g_object_unref(mge_item);
}

// ! `MgeItem` class definitions ! //

MgeItem*
mge_item_new(const gchar* key,
             const gchar* value)
{
  MgeItem* self = g_object_new(MGE_TYPE_ITEM, NULL);
  self->key = g_strdup(key);
  self->value = g_strdup(value);
  return self;
}

static GType
mge_item_get_type_once(void)
{
  static const GTypeInfo type_info = {
    .class_size = sizeof(MgeItemClass),
    .base_init = NULL,
    .base_finalize = NULL,
    .class_init = (GClassInitFunc) NULL,
    .class_finalize = NULL,
    .class_data = NULL,
    .instance_size = sizeof(MgeItem),
    .n_preallocs = 0,
    .instance_init = (GInstanceInitFunc) NULL,
    .value_table = NULL
  };

  GType type_id = g_type_register_static(
    g_object_get_type(),
    "MgeItem",
    &type_info,
    0
  );

  return type_id;
}

GType
mge_item_get_type(void)
{
  static volatile gsize type_once = 0;

  if (g_once_init_enter(&type_once)) {
    GType type_id = mge_item_get_type_once();
    g_once_init_leave(&type_once, type_id);
  }

  return type_once;
}