#include <gtk/gtk.h>

typedef struct _TreeItem TreeItem;

struct _TreeItem {
  gboolean        enabled;
  const gchar    *label;
  TreeItem       *child;
};

enum {
  ENABLED_COLUMN = 0,
  LABEL_COLUMN,
  NUM_COLUMNS
};

TreeItem row1[] = {
  { TRUE, "Sublime Text", NULL },
  { TRUE, "VS Code", NULL },
  { TRUE, "Atom", NULL }
};

TreeItem row2[] = {
  { TRUE, "Spotify", NULL },
  { TRUE, "Deezer", NULL },
  { TRUE, "SoundCloud", NULL }
};

TreeItem row3[] = {
  { TRUE, "Edge", NULL },
  { TRUE, "Chrome", NULL },
  { TRUE, "Firefox", NULL }
};

TreeItem rows[] = {
  { TRUE, "Code editors", row1 },
  { TRUE, "Music services", row2 },
  { TRUE, "Web browsers", row3 }
};

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
GtkWidget* build_tree_view();
GtkTreeModel* create_model();
void add_columns(GtkTreeView *treeview);
void cell_toggled(GtkCellRendererToggle *cell, char *path, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.TreeView";
  GtkApplication *app = gtk_application_new(app_id, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", GTK_APPLICATION(self),
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkGrid",
    NULL
  );

  gtk_container_add(GTK_CONTAINER(win), build_tree_view());
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

GtkWidget* build_tree_view() {
  GtkWidget *view = g_object_new(GTK_TYPE_TREE_VIEW, "visible", TRUE, NULL);

  GtkTreeModel *model = create_model();
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

  add_columns(GTK_TREE_VIEW(view));
  g_object_unref(model);
  g_signal_connect(view, "realize", G_CALLBACK(gtk_tree_view_expand_all), NULL);

  return view;
}

GtkTreeModel* create_model() {
  TreeItem *data = rows;
  GtkTreeIter iter;
  GtkTreeStore *model = gtk_tree_store_new(NUM_COLUMNS, G_TYPE_BOOLEAN, G_TYPE_STRING);

  while (data->enabled) {
    TreeItem *child = data->child;

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

void add_columns(GtkTreeView *view) {
  GtkCellRenderer *cell;

  cell = gtk_cell_renderer_toggle_new();
  gtk_tree_view_insert_column_with_attributes(view, -1, "Enabled", cell, "active", ENABLED_COLUMN, NULL);
  g_signal_connect(cell, "toggled", G_CALLBACK(cell_toggled), view);

  cell = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(view, -1, "App", cell, "text", LABEL_COLUMN, NULL);
}

void cell_toggled(GtkCellRendererToggle *self, char *path_str, gpointer data) {
  GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(data));
  GtkTreePath  *path  = gtk_tree_path_new_from_string((const gchar *) path_str);

  GtkTreeIter iter;
  gboolean active;
  gint *col_pos;

  col_pos = g_object_get_data (G_OBJECT (self), "column");

  gtk_tree_model_get_iter(model, &iter, path);
  gtk_tree_model_get(model, &iter, col_pos, &active, -1);

  active = (active) ? FALSE : TRUE;
  gtk_tree_store_set(GTK_TREE_STORE(model), &iter, col_pos, active, -1);
  gtk_tree_path_free (path);
}