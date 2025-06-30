#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
gboolean onDrawSquare(GtkWidget *self, cairo_t *cr, gpointer data);
gboolean onDrawCircle(GtkWidget *self, cairo_t *cr, gpointer data);
gboolean onDrawTriangle(GtkWidget *self, cairo_t *cr, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.DrawingArea";
const gchar *appTitle = "GtkDrawingArea";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *squareDrawingArea = gtk_drawing_area_new();
  GtkWidget *circleDrawingArea = gtk_drawing_area_new();
  GtkWidget *triangleDrawingArea = gtk_drawing_area_new();

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), squareDrawingArea, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), circleDrawingArea, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), triangleDrawingArea, FALSE, FALSE, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_show_all(box);

  gtk_widget_set_size_request(squareDrawingArea, 80, 80);
  g_signal_connect(squareDrawingArea, "draw", G_CALLBACK(onDrawSquare), NULL);

  gtk_widget_set_size_request(circleDrawingArea, 80, 80);
  g_signal_connect(circleDrawingArea, "draw", G_CALLBACK(onDrawCircle), NULL);

  gtk_widget_set_size_request(triangleDrawingArea, 80, 80);
  g_signal_connect(
    triangleDrawingArea,
    "draw",
    G_CALLBACK(onDrawTriangle),
    NULL
  );
}

gboolean onDrawSquare(GtkWidget *self, cairo_t *cr, gpointer data) {
  GtkStyleContext *context = gtk_widget_get_style_context(self);
  GtkStateFlags flags = gtk_style_context_get_state(context);
  int width = gtk_widget_get_allocated_width(self);
  int height = gtk_widget_get_allocated_height(self);
  GdkRGBA color;

  cairo_rectangle(cr, 0, 0, width, height);
  gtk_style_context_get_color(context, flags, &color);
  gdk_cairo_set_source_rgba(cr, &color);
  cairo_fill(cr);

  return TRUE;
}

gboolean onDrawCircle(GtkWidget *self, cairo_t *cr, gpointer data) {
  GtkStyleContext *context = gtk_widget_get_style_context(self);
  GtkStateFlags flags = gtk_style_context_get_state(context);
  int width = gtk_widget_get_allocated_width(self);
  int height = gtk_widget_get_allocated_height(self);
  double xc = width / 2.0;
  double yc = height / 2.0;
  double radius = MIN(width, height) / 2.0;
  GdkRGBA color;

  cairo_arc(cr, xc, yc, radius, 0, 2 * G_PI);
  gtk_style_context_get_color(context, flags, &color);
  gdk_cairo_set_source_rgba(cr, &color);
  cairo_fill(cr);

  return TRUE;
}

gboolean onDrawTriangle(GtkWidget *self, cairo_t *cr, gpointer data) {
  GtkStyleContext *context = gtk_widget_get_style_context(self);
  GtkStateFlags flags = gtk_style_context_get_state(context);
  int width = gtk_widget_get_allocated_width(self);
  int height = gtk_widget_get_allocated_height(self);
  GdkRGBA color;

  cairo_move_to(cr, width / 2.0, 0);
  cairo_line_to(cr, 0, height);
  cairo_line_to(cr, width, height);
  cairo_close_path(cr);

  gtk_style_context_get_color(context, flags, &color);
  gdk_cairo_set_source_rgba(cr, &color);
  cairo_fill(cr);

  return TRUE;
}