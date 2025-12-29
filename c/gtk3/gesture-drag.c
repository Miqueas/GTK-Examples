#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_drag_begin(double start_x, double start_y);
static void on_drag_update(double offset_x, double offset_y);
static void on_drag_end(double offset_x, double offset_y);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.GestureDrag";
const static gchar* APP_TITLE = "GtkGestureDrag";

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
  GtkGesture* gesture_drag = gtk_gesture_drag_new(window);

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  g_signal_connect(gesture_drag, "drag-begin", G_CALLBACK(on_drag_begin), NULL);
  g_signal_connect(gesture_drag, "drag-update", G_CALLBACK(on_drag_update), NULL);
  g_signal_connect(gesture_drag, "drag-end", G_CALLBACK(on_drag_end), NULL);
}

static void on_drag_begin(double start_x, double start_y) {
  g_print("Drag started at: (%f, %f)\n", start_x, start_y);
}

static void on_drag_update(double offset_x, double offset_y) {
  g_print("Drag updated with offset: (%f, %f)\n", offset_x, offset_y);
}

static void on_drag_end(double offset_x, double offset_y) {
  g_print("Drag ended with offset: (%f, %f)\n", offset_x, offset_y);
}