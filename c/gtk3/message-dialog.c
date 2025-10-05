#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.MessageDialog";
const static gchar* APP_TITLE = "GtkMessageDialog";
const static gchar* TITLE_TEXT = "<span size=\"x-large\" font-weight=\"bold\">Universe destruction</span>";
const static gchar* SUMMARY_TEXT = "Our universe has a lot of problems and the only way to fix\n"
"it is destroying the entire universe and this important decision\nis now in your hands.";

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

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* dialog = gtk_message_dialog_new(
    NULL,
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_QUESTION,
    GTK_BUTTONS_NONE,
    NULL
  );

  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(dialog));

  g_object_set(dialog, "text", TITLE_TEXT, NULL);
  g_object_set(dialog, "use-markup", TRUE, NULL);
  g_object_set(dialog, "secondary-text", SUMMARY_TEXT, NULL);
  gtk_window_set_title(GTK_WINDOW(dialog), APP_TITLE);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes 👍", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "No 🛑", GTK_RESPONSE_CANCEL);
}