#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onFontActivated(GtkFontChooser *self, gchar *fontname, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FontChooserWidget";
const gchar *APP_TITLE = "GtkFontChooserWidget";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *widget = gtk_font_chooser_widget_new();
  GtkWidget *hintLabel = gtk_label_new("Double click a font to activate it");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), widget, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), hintLabel, FALSE, TRUE, 0);
  gtk_widget_show_all(box);

  gtk_widget_show(widget);
  g_signal_connect(widget, "font-activated", G_CALLBACK(onFontActivated), NULL);
  gtk_widget_set_size_request(widget, 380, 600);
}

void onFontActivated(GtkFontChooser *self, gchar *fontname, gpointer data) {
  g_print("Font: %s\n", fontname);
}