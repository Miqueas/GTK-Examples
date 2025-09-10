#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onFileSet(GtkFileChooserButton *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserButton";
const gchar *APP_TITLE = "GtkFileChooserButton";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *box, *hintText, *button, *outputText;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  hintText = gtk_label_new("Open a file");
  button = gtk_file_chooser_button_new("", GTK_FILE_CHOOSER_ACTION_OPEN);
  outputText = gtk_label_new("");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(box), hintText, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), button, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), outputText, FALSE, TRUE, 0);
  gtk_widget_show_all(box);

  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  g_signal_connect(button, "file-set", G_CALLBACK(onFileSet), outputText);

  gtk_label_set_line_wrap(GTK_LABEL(outputText), TRUE);
}

void onFileSet(GtkFileChooserButton *self, gpointer data) {
  gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(self));
  g_object_set(data, "label", g_strconcat("Selected file: ", filename, NULL), NULL);
}