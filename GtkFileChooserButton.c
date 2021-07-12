#include <gtk/gtk.h>

void app_activate(GtkApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void on_file_set(GtkFileChooserButton *self, gpointer data);

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.c-gtk-examples.GtkFileChooserButton",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GtkApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));

  GtkWidget *box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "spacing", 10,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  GtkWidget *button = g_object_new(
    GTK_TYPE_FILE_CHOOSER_BUTTON,
    "visible", TRUE,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  GtkWidget *label = g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "wrap", TRUE, NULL);

  gtk_box_pack_start(GTK_BOX(box), g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "Open a file", NULL), FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), button, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), label, FALSE, TRUE, 0);

  g_signal_connect(button, "file-set", G_CALLBACK(on_file_set), label);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "My App",
    "subtitle", "An awesome app that you'll love",
    NULL
  );

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

void on_file_set(GtkFileChooserButton *self, gpointer data) {
  gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(self));
  g_object_set(data, "label", g_strconcat("Selected file: ", filename, NULL), NULL);
}