#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AppChooserDialog";
const static gchar* APP_TITLE = "GtkAppChooserDialog";

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

  if (window == NULL) {
    g_printerr("No active window found.\n");
    return;
  }

  gint result = gtk_dialog_run(GTK_DIALOG(window));

  switch (result) {
    case GTK_RESPONSE_OK: {
      GAppInfo* info = gtk_app_chooser_get_app_info(GTK_APP_CHOOSER(window));
      g_print("ID: %s\n", g_app_info_get_id(info));
      g_print("Executable: %s\n", g_app_info_get_executable(info));
      g_print("Description: %s\n", g_app_info_get_description(info));
      g_print("Commandline: %s\n", g_app_info_get_commandline(info));
      g_print("Display name: %s\n", g_app_info_get_display_name(info));
      break;
    }
    default: break;
  }

  gtk_widget_destroy(GTK_WIDGET(window));
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* dialog = gtk_app_chooser_dialog_new_for_content_type(NULL, 0, "image/png");

  gtk_window_set_title(GTK_WINDOW(dialog), APP_TITLE);
  gtk_window_set_application(GTK_WINDOW(dialog), GTK_APPLICATION(self));
  gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
}