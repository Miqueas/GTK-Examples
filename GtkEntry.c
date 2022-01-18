#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void on_entry_changed(GtkWidget *self, GdkEvent *ev, gpointer data);

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.C-GTK3-Examples.GtkEntry",
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

  GtkWidget *label = g_object_new(GTK_TYPE_LABEL, "visible", TRUE, NULL);
  GtkWidget *entry = g_object_new(GTK_TYPE_ENTRY, "visible", TRUE, NULL);

  GtkWidget *box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "spacing", 10,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  gtk_box_pack_start(
    GTK_BOX(box),
    g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "Enter some text", NULL),
    FALSE, TRUE, 0
  );

  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), label, FALSE, TRUE, 0);
  
  g_signal_connect(entry, "key-release-event", G_CALLBACK(on_entry_changed), label);

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
    "title", "GtkEntry",
    "subtitle", "Example 1",
    NULL
  );

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

void on_entry_changed(GtkWidget *self, GdkEvent *ev, gpointer data) {
  char *text;
  g_object_get(self, "text", &text, NULL);
  g_object_set(data, "label", text, NULL);
}
