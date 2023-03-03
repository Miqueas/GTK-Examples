#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.Dialog2";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
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
  GtkWidget *dialog, *header, *title, *summary, *epilog, *content;
  const char *title_text = "<span size=\"x-large\" font-weight=\"bold\">Universe destruction</span>";
  const char *summary_text = "Our universe has a lot of problems and the only way to fix\nit is destroying the entire universe and this important decision\nis now in your hands.";
  const char *epilog_text = "<span size=\"large\" font-weight=\"bold\">Do you accept?</span>";

  // "use-header-bar" is a Construct Only property
  dialog = g_object_new(GTK_TYPE_DIALOG, "use-header-bar", TRUE, NULL);
  header = gtk_dialog_get_header_bar(GTK_DIALOG(dialog));
  title = gtk_label_new(title_text);
  summary = gtk_label_new(summary_text);
  epilog = gtk_label_new(epilog_text);
  content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

  GtkWidget *widgets[5] = { header, title, summary, epilog, content };

  for (int i = 0; i < 5; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes 👍", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "No 🛑", GTK_RESPONSE_CANCEL);
  gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
  gtk_window_set_application(GTK_WINDOW(dialog), GTK_APPLICATION(self));

  gtk_header_bar_set_title(GTK_HEADER_BAR(header), "GtkDialog");
  gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header), "Example 2");

  gtk_label_set_use_markup(GTK_LABEL(title), TRUE);

  gtk_label_set_xalign(GTK_LABEL(summary), 0);
  gtk_label_set_line_wrap(GTK_LABEL(summary), TRUE);
  gtk_label_set_line_wrap_mode(GTK_LABEL(summary), PANGO_WRAP_CHAR);

  gtk_label_set_use_markup(GTK_LABEL(epilog), TRUE);

  gtk_box_set_spacing(GTK_BOX(content), 10);
  gtk_box_pack_start(GTK_BOX(content), title, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(content), summary, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(content), epilog, FALSE, TRUE, 10);
}
