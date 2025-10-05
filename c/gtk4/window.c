#include <gtk/gtk.h>

gint main(void) {
  // In GTK 4, this function no longer requires the `argc` and `argv` parameters
  gtk_init();

  GtkWidget* win = gtk_window_new();
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  // I think this is optional
  // g_signal_connect(win, "destroy", G_CALLBACK(gtk_window_close), win);
  gtk_window_present(GTK_WINDOW(win));

  // In GTK 4, all the `gtk_main` API and family was remove
  while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0)
    g_main_context_iteration(NULL, TRUE);

  return 0;
}