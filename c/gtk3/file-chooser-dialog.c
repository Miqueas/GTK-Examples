#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserDialog";
const static gchar* APP_TITLE = "GtkFileChooserDialog";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gint result = gtk_dialog_run(GTK_DIALOG(window));

  switch (result) {
    case GTK_RESPONSE_OK: {
      gchar* name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(window));
      g_print("You selected: %s\n", name);
      break;
    }

    case GTK_RESPONSE_CANCEL: {
      g_print("Canceled\n");
      break;
    }

    default: {
      g_print("Something else\n");
      break;
    }
  }

  gtk_widget_destroy(GTK_WIDGET(window));
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_file_chooser_dialog_new(APP_TITLE, NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL, NULL);
  gtk_dialog_add_button(GTK_DIALOG(window), "Open", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(window), "Cancel", GTK_RESPONSE_CANCEL);
  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(window));
}