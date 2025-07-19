#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Dialog2";
const gchar *appTitle = "GtkDialog";
const gchar *titleText = "<span size='x-large' font-weight='bold'>"
"Universe destruction</span>";
const gchar *epilogText = "<span size='large' font-weight='bold'>"
"Do you accept?</span>";
const gchar *summaryText = "Our universe has a lot of problems and the only "
"way to fix\nit is destroying the entire universe and this important decision"
"\nis now in your hands.";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
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

void onAppStartup(GApplication *self, gpointer data) {
  // "use-header-bar" is a Construct Only property
  GtkWidget* dialog = g_object_new(GTK_TYPE_DIALOG, "use-header-bar", TRUE, NULL);
  GtkWidget* headerBar = gtk_dialog_get_header_bar(GTK_DIALOG(dialog));
  GtkWidget* titleLabel = gtk_label_new(titleText);
  GtkWidget* summaryLabel = gtk_label_new(summaryText);
  GtkWidget* epilogLabel = gtk_label_new(epilogText);
  GtkWidget* contentBox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

  gtk_dialog_add_button(GTK_DIALOG(dialog), "Yes 👍", GTK_RESPONSE_OK);
  gtk_dialog_add_button(GTK_DIALOG(dialog), "No 🛑", GTK_RESPONSE_CANCEL);
  gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
  gtk_window_set_application(GTK_WINDOW(dialog), GTK_APPLICATION(self));

  gtk_header_bar_set_title(GTK_HEADER_BAR(headerBar), "GtkDialog");
  gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerBar), "Example 2");

  gtk_label_set_use_markup(GTK_LABEL(titleLabel), TRUE);

  gtk_label_set_xalign(GTK_LABEL(summaryLabel), 0);
  gtk_label_set_line_wrap(GTK_LABEL(summaryLabel), TRUE);
  gtk_label_set_line_wrap_mode(GTK_LABEL(summaryLabel), PANGO_WRAP_CHAR);

  gtk_label_set_use_markup(GTK_LABEL(epilogLabel), TRUE);

  gtk_box_set_spacing(GTK_BOX(contentBox), 10);
  gtk_box_pack_start(GTK_BOX(contentBox), titleLabel, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(contentBox), summaryLabel, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(contentBox), epilogLabel, FALSE, TRUE, 10);
}
