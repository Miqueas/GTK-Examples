#include <gtk/gtk.h>

// `GtkScrolledWindow` is a container that provides a scrolling view of its
// child widget

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ScrolledWindow";
const static gchar* APP_TITLE = "GtkScrolledWindow";

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
  GtkWidget* scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
  GtkWidget* textView = gtk_text_view_new();
  GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

  gtk_container_add(GTK_CONTAINER(window), scrolledWindow);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_container_add(GTK_CONTAINER(scrolledWindow), textView);
  gtk_widget_show_all(scrolledWindow);

  for (gint i = 0; i < 10000; i++) {
    gtk_text_buffer_insert_at_cursor(
      buffer,
      g_strdup_printf("Text %d\n", i + 1),
      -1
    );
  }
}