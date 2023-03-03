#include <gtk/gtk.h>

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_present(GTK_WINDOW(win));
  gtk_main();

  return 0;
}