#include <gtk/gtk.h>

// `GtkEventBox` Allows to capture events on widgets that do not normally
// receive them. It can also be used to capture events that aren't implemented
// by the widget itself. This widget is deprecated in GTK 4 and was replaced by
// event controllers and the fact that all widgets can now receive events.

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
gboolean onClicked(GtkWidget* self, GdkEventButton event, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.EventBox";
const static gchar* APP_TITLE = "GtkEventBox";

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
  GtkWidget* eventBox = gtk_event_box_new();
  GtkWidget* label = gtk_label_new("Click me!");

  gtk_container_add(GTK_CONTAINER(window), eventBox);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_container_add(GTK_CONTAINER(eventBox), label);
  gtk_widget_show_all(eventBox);
  g_signal_connect(eventBox, "button-press-event", G_CALLBACK(onClicked), NULL);
}

gboolean onClicked(GtkWidget* self, GdkEventButton event, gpointer data) {
  g_print("Clicked\n");
  return FALSE;
}