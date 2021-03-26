#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.c-gtk-examples.GtkMessageDialog",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

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
      gtk_widget_destroy(GTK_WIDGET(win));
      g_print("Universe destroyed! 💥\n");
      break;
    }

    case GTK_RESPONSE_CANCEL: {
      gtk_widget_destroy(GTK_WIDGET(win));
      g_print("Universe is in peace now! 🙏\n");
      break;
    }

    default: {
      gtk_widget_destroy(GTK_WIDGET(win));
      g_print("Nothing happens! 🤔\n");
      break;
    }
  }
}

void app_startup(GApplication *self, gpointer data) {
  char *title = "<span size=\"x-large\" font-weight=\"bold\">Universe destruction</span>";
  char *summary = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands.\0";

  GtkWidget *dialog = g_object_new(
    GTK_TYPE_MESSAGE_DIALOG,
    "application", GTK_APPLICATION(self),
    "buttons", GTK_BUTTONS_NONE,
    "title", "GtkMessageDialog",
    "text", title,
    "use-markup", TRUE,
    "secondary-text", summary,
    NULL
  );

  gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes 👍", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "No 🛑", GTK_RESPONSE_CANCEL);
}
