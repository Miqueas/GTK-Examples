#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.C-GTK3-Examples.GtkDialog",
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
  GtkWidget *dialog = g_object_new(
    GTK_TYPE_DIALOG,
    "application", GTK_APPLICATION(self),
    "title", "GtkDialog",
    "border-width", 10,
    NULL
  );

  gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes 👍", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "No 🛑", GTK_RESPONSE_CANCEL);

  char *title_text = "<span size=\"x-large\" font-weight=\"bold\">Universe destruction</span>";
  GtkWidget *title = g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", title_text,
    "use-markup", TRUE,
    NULL
  );

  char *summary_text = "Our universe has a lot of problems and the only way to fix\nit is destroying the entire universe and this important decision\nis now in your hands.";
  GtkWidget *summary = g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", summary_text,
    "xalign", 0,
    "wrap", TRUE,
    "wrap-mode", PANGO_WRAP_CHAR,
    NULL
  );

  char *epilog_text = "<span size=\"large\" font-weight=\"bold\">Do you accept?</span>";
  GtkWidget *epilog = g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", epilog_text,
    "use-markup", TRUE,
    NULL
  );

  GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
  gtk_box_set_spacing(GTK_BOX(content), 10);
  gtk_box_pack_start(GTK_BOX(content), title, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(content), summary, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(content), epilog, FALSE, TRUE, 10);
}
