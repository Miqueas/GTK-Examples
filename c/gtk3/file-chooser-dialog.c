#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserDialog";
const gchar *appTitle = "GtkFileChooserDialog";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  int result = gtk_dialog_run(GTK_DIALOG(window));

  switch (result) {
    case GTK_RESPONSE_OK: {
      gchar *name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(window));
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

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window = gtk_file_chooser_dialog_new(appTitle, NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL, NULL);
  gtk_dialog_add_button(GTK_DIALOG(window), "Open", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(window), "Cancel", GTK_RESPONSE_CANCEL);
  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(window));
}