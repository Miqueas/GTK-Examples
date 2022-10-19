#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK-Examples.Gtk4.HeaderBar";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
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

  GtkWidget *title_label = g_object_new(
    GTK_TYPE_LABEL,
    "label", "<span weight='bold'>My app</span>",
    "use-markup", TRUE,
    NULL
  );

  GtkWidget *subtitle_label = g_object_new(
    GTK_TYPE_LABEL,
    "label", "An awesome app that you'll love",
    NULL
  );

  GtkWidget *title_box = g_object_new(
    GTK_TYPE_BOX,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "margin-top", 4,
    "margin-bottom", 4,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  gtk_box_append(GTK_BOX(title_box), title_label);
  gtk_box_append(GTK_BOX(title_box), subtitle_label);

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "show-title-buttons", TRUE,
    "title-widget", title_box,
    NULL
  );

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}