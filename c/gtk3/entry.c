#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void on_entry_changed(GtkWidget *self, GdkEvent *ev, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.Entry";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

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
  GtkWidget *win, *label, *entry, *box;
  
  win = gtk_application_window_new(GTK_APPLICATION(self));
  label = gtk_label_new("");
  entry = gtk_entry_new();
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  GtkWidget *widgets[] = { label, entry, box };

  for (int i = 0; i < 3; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
  gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_CHAR);
  gtk_label_set_max_width_chars(GTK_LABEL(label), 18);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  gtk_box_pack_start(
    GTK_BOX(box),
    g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "Enter some text", NULL),
    FALSE, TRUE, 0
  );

  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), label, FALSE, TRUE, 0);
  
  g_signal_connect(entry, "key-release-event", G_CALLBACK(on_entry_changed), label);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);
}

void on_entry_changed(GtkWidget *self, GdkEvent *ev, gpointer data) {
  char *text;
  g_object_get(self, "text", &text, NULL);
  g_object_set(data, "label", text, NULL);
}
