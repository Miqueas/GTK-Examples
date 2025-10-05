#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Expander";
const static gchar* APP_TITLE = "GtkExpander";
const static gchar* EXPANDER_LABEL = "  <span size=\"large\" font_weight=\"bold\">Lorem ipsum</span>  ";
const static gchar* LOREM_TEXT = "Duis in metus eros. Duis faucibus rutrum eros eu vestibulum.\n"
"Proin et arcu nulla. Etiam at lacinia nibh. Vivamus pellentesque nunc nibh,\n"
"ac dignissim massa lobortis ut. Integer eu felis in elit semper ullamcorper\n"
"at in ipsum. Suspendisse tempus massa vel nibh tristique vestibulum.\n"
"Vestibulum varius eu nunc eu interdum. Curabitur pulvinar velit in purus\n"
"facilisis, et auctor augue consequat. Donec finibus felis ligula, a convallis\n"
"justo tristique a.";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* expander = gtk_expander_new(EXPANDER_LABEL);
  GtkWidget* expanderText = gtk_label_new(LOREM_TEXT);

  gtk_container_add(GTK_CONTAINER(window), expander);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_set_visible(expander, TRUE);
  gtk_container_add(GTK_CONTAINER(expander), expanderText);
  gtk_expander_set_use_markup(GTK_EXPANDER(expander), TRUE);
  gtk_expander_set_resize_toplevel(GTK_EXPANDER(expander), TRUE);

  gtk_widget_set_visible(expanderText, TRUE);
  gtk_label_set_line_wrap(GTK_LABEL(expanderText), TRUE);
}