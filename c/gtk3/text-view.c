#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkTextView";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

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
    "title", "GtkTextView",
    NULL
  );

  const gchar *lorem_ipsum = "Duis in metus eros. Duis faucibus rutrum eros eu vestibulum."
  "Proin et arcu nulla. Etiam at lacinia nibh. Vivamus pellentesque nunc nibh,"
  "ac dignissim massa lobortis ut. Integer eu felis in elit semper ullamcorper"
  "at in ipsum. Suspendisse tempus massa vel nibh tristique vestibulum."
  "Vestibulum varius eu nunc eu interdum. Curabitur pulvinar velit in purus"
  "facilisis, et auctor augue consequat. Donec finibus felis ligula, a convallis"
  "justo tristique a.\0";

  GtkWidget *tv = g_object_new(
    GTK_TYPE_TEXT_VIEW,
    "visible", TRUE,
    "editable", FALSE,
    "wrap-mode", GTK_WRAP_WORD,
    NULL
  );

  GtkTextBuffer *tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
  gtk_text_buffer_set_text(GTK_TEXT_BUFFER(tb), lorem_ipsum, -1);

  gtk_container_add(GTK_CONTAINER(win), tv);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}