#include <gtk/gtk.h>

int main(int argc, char **argv) {
  gtk_init();

  GtkWidget *win = g_object_new(
    GTK_TYPE_WINDOW,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  g_signal_connect(win, "destroy", G_CALLBACK(gtk_window_close), win);
  gtk_window_present(GTK_WINDOW(win));

  while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0)
    g_main_context_iteration(NULL, TRUE);

  return 0;
}