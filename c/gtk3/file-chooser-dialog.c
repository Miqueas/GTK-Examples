#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserDialog";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  int res = gtk_dialog_run(GTK_DIALOG(win));

  switch (res) {
    case GTK_RESPONSE_OK: {
      gchar *name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(win));
      gtk_widget_destroy(GTK_WIDGET(win));
      g_print("You selected: %s\n", name);
      break;
    }

    case GTK_RESPONSE_CANCEL: {
      gtk_widget_destroy(GTK_WIDGET(win));
      g_print("Canceled\n");
      break;
    }

    default: {
      gtk_widget_destroy(GTK_WIDGET(win));
      g_print("Something else\n");
      break;
    }
  }
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_FILE_CHOOSER_DIALOG,
    "title", "Select a file",
    "action", GTK_FILE_CHOOSER_ACTION_OPEN,
    NULL
  );

  gtk_dialog_add_button(GTK_DIALOG(win), "Open", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(win), "Cancel", GTK_RESPONSE_CANCEL);

  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(win));
}