#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_color_set(GtkColorButton* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ColorButton";
const static gchar* APP_TITLE = "GtkColorButton";

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
  GtkWidget* window, *colorButton;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  colorButton = gtk_color_button_new();

  gtk_container_add(GTK_CONTAINER(window), colorButton);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_halign(colorButton, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(colorButton, GTK_ALIGN_CENTER);
  gtk_widget_set_visible(colorButton, TRUE);
  gtk_color_button_set_title(GTK_COLOR_BUTTON(colorButton), "Pick a color");
  g_signal_connect(colorButton, "color-set", G_CALLBACK(on_color_set), NULL);
}

static void on_color_set(GtkColorButton* self, gpointer data) {
  GdkRGBA color;
  gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(self), &color);
  g_print("Color: %s\n", gdk_rgba_to_string(&color));
}