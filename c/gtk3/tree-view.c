#include <gtk/gtk.h>

typedef struct _TreeItem TreeItem;

struct _TreeItem {
  gboolean enabled;
  const gchar* label;
  TreeItem* child;
};

enum {
  ENABLED_COLUMN = 0,
  LABEL_COLUMN,
  NUM_COLUMNS
};

void app_activate(GApplication* self, gpointer data);
void app_startup(GApplication* self, gpointer data);
GtkTreeModel* create_model();
void add_columns(GtkTreeView* treeview);
void on_cell_toggled(GtkCellRendererToggle* cell, gchar* path, gpointer data);

static TreeItem ROW1[] = {
  { TRUE, "Sublime Text", NULL },
  { TRUE, "VS Code", NULL },
  { TRUE, "Atom", NULL }
};

static TreeItem ROW2[] = {
  { TRUE, "Spotify", NULL },
  { TRUE, "Deezer", NULL },
  { TRUE, "SoundCloud", NULL }
};

static TreeItem ROW3[] = {
  { TRUE, "Edge", NULL },
  { TRUE, "Chrome", NULL },
  { TRUE, "Firefox", NULL }
};

static TreeItem ROWS[] = {
  { TRUE, "Code editors", ROW1 },
  { TRUE, "Music services", ROW2 },
  { TRUE, "Web browsers", ROW3 }
};

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.TreeView";
const static gchar* APP_TITLE = "GtkTreeView";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

void app_startup(GApplication* self, gpointer data) {
  GtkTreeModel* model = create_model();
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* tree_view = gtk_tree_view_new_with_model(model);
  
  gtk_container_add(GTK_CONTAINER(window), tree_view);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  
  add_columns(GTK_TREE_VIEW(tree_view));
  g_signal_connect(tree_view, "realize", G_CALLBACK(gtk_tree_view_expand_all), NULL);
  gtk_widget_show_all(tree_view);

  g_object_unref(model);
}

GtkTreeModel* create_model() {
  GtkTreeStore* model = gtk_tree_store_new(NUM_COLUMNS, G_TYPE_BOOLEAN, G_TYPE_STRING);
  GtkTreeIter iter;
  TreeItem* data = ROWS;

  while (data->enabled) {
    TreeItem* child = data->child;

    gtk_tree_store_append(model, &iter, NULL);
    gtk_tree_store_set(model, &iter,
      ENABLED_COLUMN, data->enabled,
      LABEL_COLUMN, data->label,
      -1
    );

    while (child->enabled) {
      GtkTreeIter child_iter;

      gtk_tree_store_append(model, &child_iter, &iter);
      gtk_tree_store_set(model, &child_iter,
        ENABLED_COLUMN, child->enabled,
        LABEL_COLUMN, child->label,
        -1
      );

      child++;
    }

    data++;
  }

  return GTK_TREE_MODEL(model);
}

void add_columns(GtkTreeView* tree_view) {
  GtkCellRenderer* cell = gtk_cell_renderer_toggle_new();
  gtk_tree_view_insert_column_with_attributes(tree_view, -1, "Enabled", cell,
    "active", ENABLED_COLUMN,
    NULL
  );
  g_signal_connect(cell, "toggled", G_CALLBACK(on_cell_toggled), tree_view);

  cell = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(tree_view, -1, "App", cell,
    "text", LABEL_COLUMN,
    NULL
  );
}

void on_cell_toggled(GtkCellRendererToggle* self, gchar* path_str, gpointer data) {
  GtkTreeModel* model = gtk_tree_view_get_model(GTK_TREE_VIEW(data));
  GtkTreePath* path  = gtk_tree_path_new_from_string((const gchar*) path_str);
  GtkTreeIter iter;
  gboolean active;
  gint* col_pos = g_object_get_data(G_OBJECT(self), "column");

  gtk_tree_model_get_iter(model, &iter, path);
  gtk_tree_model_get(model, &iter, col_pos, &active, -1);

  active = (active) ? FALSE : TRUE;
  gtk_tree_store_set(GTK_TREE_STORE(model), &iter, col_pos, active, -1);
  gtk_tree_path_free(path);
}