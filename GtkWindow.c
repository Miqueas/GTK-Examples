#include <gtk/gtk.h>

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  GtkWidget *win = g_object_new(
    GTK_TYPE_WINDOW,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_present(GTK_WINDOW(win));
  gtk_main();

  return 0;
}