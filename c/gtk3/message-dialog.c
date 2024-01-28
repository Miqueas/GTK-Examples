#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.MessageDialog";
const gchar *appTitle = "GtkMessageDialog";
const gchar *titleText = "<span size=\"x-large\" font-weight=\"bold\">Universe destruction</span>";
const gchar *summaryText = "Our universe has a lot of problems and the only way to fix\n"
"it is destroying the entire universe and this important decision\nis now in your hands.";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gint result = gtk_dialog_run(GTK_DIALOG(window));
  gtk_widget_destroy(GTK_WIDGET(window));

  switch (result) {
    case GTK_RESPONSE_OK: {
      g_print("Universe destroyed! 💥\n");
      break;
    }

    case GTK_RESPONSE_CANCEL: {
      g_print("Universe is in peace now! 🙏\n");
      break;
    }

    default: {
      g_print("Nothing happens! 🤔\n");
      break;
    }
  }
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_NONE, NULL);

  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(dialog));

  g_object_set(dialog, "text", titleText, NULL);
  g_object_set(dialog, "use-markup", TRUE, NULL);
  g_object_set(dialog, "secondary-text", summaryText, NULL);
  gtk_window_set_title(GTK_WINDOW(dialog), appTitle);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes 👍", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "No 🛑", GTK_RESPONSE_CANCEL);
}
