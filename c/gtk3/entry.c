#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
void on_entry_changed(GtkEditable* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Entry";
const static gchar* APP_TITLE = "GtkEntry";

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
  GtkWidget* window, *box, *hintLabel, *entry, *outputLabel;
  
  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  hintLabel = gtk_label_new("Enter some text");
  entry = gtk_entry_new();
  outputLabel = gtk_label_new("");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  g_signal_connect(entry, "changed", G_CALLBACK(on_entry_changed), outputLabel);

  gtk_box_pack_start(GTK_BOX(box), hintLabel, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), outputLabel, FALSE, TRUE, 0);

  gtk_label_set_line_wrap(GTK_LABEL(outputLabel), TRUE);
  gtk_label_set_line_wrap_mode(GTK_LABEL(outputLabel), PANGO_WRAP_CHAR);
  gtk_label_set_max_width_chars(GTK_LABEL(outputLabel), 18);

  gtk_widget_show_all(box);
}

void on_entry_changed(GtkEditable* self, gpointer data) {
  const gchar* text = gtk_entry_get_text(GTK_ENTRY(self));
  gtk_label_set_label(GTK_LABEL(data), text);
}
