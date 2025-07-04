#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onEntryChanged(GtkEditable *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Entry";
const gchar *appTitle = "GtkEntry";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

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
  GtkWidget *window, *box, *hintLabel, *entry, *outputLabel;
  
  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  hintLabel = gtk_label_new("Enter some text");
  entry = gtk_entry_new();
  outputLabel = gtk_label_new("");

  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_margin_top(box, 10);
  gtk_widget_set_margin_end(box, 10);
  gtk_widget_set_margin_bottom(box, 10);
  gtk_widget_set_margin_start(box, 10);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);  
  gtk_box_append(GTK_BOX(box), hintLabel);
  gtk_box_append(GTK_BOX(box), entry);
  gtk_box_append(GTK_BOX(box), outputLabel);
  
  gtk_label_set_wrap(GTK_LABEL(outputLabel), TRUE);
  gtk_label_set_wrap_mode(GTK_LABEL(outputLabel), PANGO_WRAP_CHAR);
  gtk_label_set_max_width_chars(GTK_LABEL(outputLabel), 18);

  g_signal_connect(entry, "changed", G_CALLBACK(onEntryChanged), outputLabel);
}

void onEntryChanged(GtkEditable *self, gpointer data) {
  const char *text = gtk_editable_get_text(self);
  gtk_label_set_label(GTK_LABEL(data), text);
}
