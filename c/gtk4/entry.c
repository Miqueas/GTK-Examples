#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_entry_changed(GtkEditable* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Entry";
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
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* hint_label = gtk_label_new("Enter some text");
  GtkWidget* entry = gtk_entry_new();
  GtkWidget* output_label = gtk_label_new("");

  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_margin_top(box, 10);
  gtk_widget_set_margin_end(box, 10);
  gtk_widget_set_margin_bottom(box, 10);
  gtk_widget_set_margin_start(box, 10);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);  
  gtk_box_append(GTK_BOX(box), hint_label);
  gtk_box_append(GTK_BOX(box), entry);
  gtk_box_append(GTK_BOX(box), output_label);
  
  gtk_label_set_wrap(GTK_LABEL(output_label), TRUE);
  gtk_label_set_wrap_mode(GTK_LABEL(output_label), PANGO_WRAP_CHAR);
  gtk_label_set_max_width_chars(GTK_LABEL(output_label), 18);

  g_signal_connect(entry, "changed", G_CALLBACK(on_entry_changed), output_label);
}

void on_entry_changed(GtkEditable* self, gpointer data) {
  const gchar* text = gtk_editable_get_text(self);
  gtk_label_set_label(GTK_LABEL(data), text);
}
