#include <gtk/gtk.h>

// `GtkNotebook` is a widget that can contain multiple widgets and switch
// between them using tabs

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Notebook";
const static gchar* APP_TITLE = "GtkNotebook";

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
  GtkWidget* notebook = gtk_notebook_new();

  gtk_container_add(GTK_CONTAINER(window), notebook);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_notebook_append_page(
    GTK_NOTEBOOK(notebook),
    gtk_label_new("Page 1"),
    gtk_label_new("Tab 1")
  );

  gtk_notebook_append_page(
    GTK_NOTEBOOK(notebook),
    gtk_label_new("Page 2"),
    gtk_label_new("Tab 2")
  );

  gtk_notebook_append_page(
    GTK_NOTEBOOK(notebook),
    gtk_label_new("Page 3"),
    gtk_label_new("Tab 3")
  );

  gtk_widget_show_all(notebook);
}