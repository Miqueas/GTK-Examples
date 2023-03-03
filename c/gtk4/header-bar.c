#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk4.HeaderBar";
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
  GtkWidget *win, *title_label, *subtitle_label, *title_box, *header;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  title_label = gtk_label_new("<span weight='bold'>My app</span>");
  subtitle_label = gtk_label_new("An awesome app that you'll love");
  title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  header = gtk_header_bar_new();

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  gtk_label_set_use_markup(GTK_LABEL(title_label), TRUE);

  gtk_widget_set_margin_top(title_box, 4);
  gtk_widget_set_margin_bottom(title_box, 4);
  gtk_widget_set_valign(title_box, GTK_ALIGN_CENTER);

  gtk_box_append(GTK_BOX(title_box), title_label);
  gtk_box_append(GTK_BOX(title_box), subtitle_label);

  // Since GTK 4, we need to manually add a title widget if we need/want it,
  // because there's no longer `title` and `subtitle` properties
  gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header), title_box);
  gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header), TRUE);
}