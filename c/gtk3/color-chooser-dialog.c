#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ColorChooserDialog";
const static gchar* APP_TITLE = "GtkColorChooserDialog";

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
  gint result = gtk_dialog_run(GTK_DIALOG(window));

  switch (result) {
    case GTK_RESPONSE_ACCEPT:
    case GTK_RESPONSE_APPLY:
    case GTK_RESPONSE_YES:
    case GTK_RESPONSE_OK: {
      GdkRGBA color;
      gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(window), &color);
      g_print("Color: %s\n", gdk_rgba_to_string(&color));
      break;
    }
    default: break;
  }

  gtk_widget_destroy(GTK_WIDGET(window));
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* dialog = gtk_color_chooser_dialog_new(NULL, NULL);

  gtk_window_set_title(GTK_WINDOW(dialog), APP_TITLE);
  gtk_window_set_application(GTK_WINDOW(dialog), GTK_APPLICATION(self));
  gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
}