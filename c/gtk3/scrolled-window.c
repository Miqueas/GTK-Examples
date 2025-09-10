#include <gtk/gtk.h>

// `GtkScrolledWindow` is a container that provides a scrolling view of its
// child widget

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ScrolledWindow";
const gchar *APP_TITLE = "GtkScrolledWindow";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
  GtkWidget *textView = gtk_text_view_new();
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

  gtk_container_add(GTK_CONTAINER(window), scrolledWindow);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_container_add(GTK_CONTAINER(scrolledWindow), textView);
  gtk_widget_show_all(scrolledWindow);

  for (int i = 0; i < 10000; i++) {
    gtk_text_buffer_insert_at_cursor(
      buffer,
      g_strdup_printf("Text %d\n", i + 1),
      -1
    );
  }
}