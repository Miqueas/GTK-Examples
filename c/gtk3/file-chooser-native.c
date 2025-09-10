#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserNative";
const gchar *APP_TITLE = "GtkFileChooserNative";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkFileChooserNative *native = gtk_file_chooser_native_new(
    APP_TITLE,
    // In normal circumstances, you should set a parent window for this dialog
    NULL,
    GTK_FILE_CHOOSER_ACTION_OPEN,
    "Open",
    "Cancel"
  );

  gtk_native_dialog_set_modal(GTK_NATIVE_DIALOG(native), TRUE);

  switch (gtk_native_dialog_run(GTK_NATIVE_DIALOG(native))) {
    case GTK_RESPONSE_ACCEPT:
    case GTK_RESPONSE_APPLY:
    case GTK_RESPONSE_YES:
    case GTK_RESPONSE_OK: {
      gchar *name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(native));
      g_print("You selected: %s\n", name);
      break;
    }
    default: break;
  }

  gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(native));
  g_object_unref(native);
}