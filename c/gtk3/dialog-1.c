#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Dialog1";
const static gchar* APP_TITLE = "GtkDialog";
const gchar* TITLE_TEXT = "<span size='x-large' font-weight='bold'>"
"Universe destruction</span>";
const gchar* EPILOG_TEXT = "<span size='large' font-weight='bold'>"
"Do you accept?</span>";
const gchar* SUMMARY_TEXT = "Our universe has a lot of problems and the only "
"way to fix\nit is destroying the entire universe and this important decision"
"\nis now in your hands.";

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
  gint result = gtk_dialog_run(GTK_DIALOG(window));
  gtk_widget_destroy(GTK_WIDGET(window));

  switch (result) {
    case GTK_RESPONSE_ACCEPT:
    case GTK_RESPONSE_APPLY:
    case GTK_RESPONSE_YES:
    case GTK_RESPONSE_OK:
      g_print("Universe destroyed! 💥\n");
      break;
    default:
      g_print("Universe is in peace now! 🙏\n");
      break;
  }
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* dialog = gtk_dialog_new();
  GtkWidget* title_label = gtk_label_new(TITLE_TEXT);
  GtkWidget* summary_label = gtk_label_new(SUMMARY_TEXT);
  GtkWidget* epilog_label = gtk_label_new(EPILOG_TEXT);
  GtkWidget* content_box = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

  gtk_window_set_title(GTK_WINDOW(dialog), APP_TITLE);
  gtk_window_set_application(GTK_WINDOW(dialog), GTK_APPLICATION(self));
  gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes 👍", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "No 🛑", GTK_RESPONSE_CANCEL);

  gtk_label_set_use_markup(GTK_LABEL(title_label), TRUE);

  gtk_label_set_xalign(GTK_LABEL(summary_label), 0);
  gtk_label_set_line_wrap(GTK_LABEL(summary_label), TRUE);
  gtk_label_set_line_wrap_mode(GTK_LABEL(summary_label), PANGO_WRAP_CHAR);

  gtk_label_set_use_markup(GTK_LABEL(epilog_label), TRUE);

  gtk_box_set_spacing(GTK_BOX(content_box), 10);
  gtk_box_pack_start(GTK_BOX(content_box), title_label, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(content_box), summary_label, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(content_box), epilog_label, FALSE, TRUE, 10);
  gtk_widget_show_all(content_box);
}