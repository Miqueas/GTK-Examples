#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
void onFileSet(GtkFileChooserButton* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserButton";
const static gchar* APP_TITLE = "GtkFileChooserButton";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* hintText = gtk_label_new("Open a file");
  GtkWidget* button = gtk_file_chooser_button_new("", GTK_FILE_CHOOSER_ACTION_OPEN);
  GtkWidget* outputText = gtk_label_new("");

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

void onFileSet(GtkFileChooserButton* self, gpointer data) {
  gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(self));
  g_object_set(data, "label", g_strconcat("Selected file: ", filename, NULL), NULL);
}