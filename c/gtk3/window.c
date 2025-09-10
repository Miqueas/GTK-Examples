#include <gtk/gtk.h>

const gchar *APP_TITLE = "GtkWindow";

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_present(GTK_WINDOW(window));
  gtk_main();

  return 0;
}