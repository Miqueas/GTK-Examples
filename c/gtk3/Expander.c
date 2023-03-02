#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkExpander";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));

  const char *lorem_ipsum = "Duis in metus eros. Duis faucibus rutrum eros eu vestibulum.\n"
  "Proin et arcu nulla. Etiam at lacinia nibh. Vivamus pellentesque nunc nibh,\n"
  "ac dignissim massa lobortis ut. Integer eu felis in elit semper ullamcorper\n"
  "at in ipsum. Suspendisse tempus massa vel nibh tristique vestibulum.\n"
  "Vestibulum varius eu nunc eu interdum. Curabitur pulvinar velit in purus\n"
  "facilisis, et auctor augue consequat. Donec finibus felis ligula, a convallis\n"
  "justo tristique a.";

  GtkWidget *expander = g_object_new(
    GTK_TYPE_EXPANDER,
    "visible", TRUE,
    "label", "  <span size=\"large\" font_weight=\"bold\">Lorem ipsum</span>  ",
    "use-markup", TRUE,
    "resize-toplevel", TRUE,
    NULL
  );

  GtkWidget *label = g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", lorem_ipsum,
    "wrap", TRUE,
    NULL
  );

  gtk_container_add(GTK_CONTAINER(expander), label);
  gtk_container_add(GTK_CONTAINER(win), expander);

  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "border-width", 10,
    "resizable", FALSE,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "My App",
    "subtitle", "An awesome app that you'll love",
    NULL
  );

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}