#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onSelectionChanged(GtkFileChooser *self, gpointer data);
void onShowHidden(GtkFileChooserWidget *self, gpointer data);
void onFileActivated(GtkFileChooser *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FileChooserWidget";
const gchar *APP_TITLE = "GtkFileChooserWidget";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
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
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *widget = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_pack_start(GTK_BOX(box), widget, TRUE, TRUE, 0);
  gtk_widget_show_all(box);

  g_signal_connect(widget, "show-hidden", G_CALLBACK(onShowHidden), NULL);
  g_signal_connect(
    widget,
    "file-activated",
    G_CALLBACK(onFileActivated),
    window
  );
  g_signal_connect(
    widget,
    "selection-changed",
    G_CALLBACK(onSelectionChanged),
    NULL
  );
}

void onShowHidden(GtkFileChooserWidget *self, gpointer data) {
  gboolean visible = gtk_file_chooser_get_show_hidden(GTK_FILE_CHOOSER(self));
  g_print("Show hidden files: %s\n", visible ? "Yes" : "No");
}

void onFileActivated(GtkFileChooser *self, gpointer data) {
  gchar *filename = gtk_file_chooser_get_filename(self);
  if (filename == NULL) {
    g_free(filename);
    return;
  }

  g_print("File chosen: %s\n", filename);
  g_free(filename);
  gtk_widget_destroy(GTK_WIDGET(data));
}

void onSelectionChanged(GtkFileChooser *self, gpointer data) {
  gchar *filename = gtk_file_chooser_get_filename(self);

  if (filename == NULL) {
    g_free(filename);
    return;
  }

  g_print("File selected: %s\n", filename);
  g_free(filename);
}