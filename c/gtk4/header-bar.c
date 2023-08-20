#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk4.HeaderBar";
const gchar *appTitle = "<span weight='bold'>GtkHeaderBar</span>";
const gchar *appSubtitle = "<span weight='light'>App subtitle</span>";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
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
  GtkWidget *window, *titleText, *subtitleText, *titleBox, *headerBar;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  titleText = gtk_label_new(appTitle);
  subtitleText = gtk_label_new(appSubtitle);
  titleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  headerBar = gtk_header_bar_new();

  gtk_window_set_titlebar(GTK_WINDOW(window), headerBar);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_label_set_use_markup(GTK_LABEL(titleText), TRUE);
  gtk_label_set_use_markup(GTK_LABEL(subtitleText), TRUE);

  gtk_widget_set_margin_top(titleBox, 4);
  gtk_widget_set_margin_bottom(titleBox, 4);
  gtk_widget_set_valign(titleBox, GTK_ALIGN_CENTER);

  gtk_box_append(GTK_BOX(titleBox), titleText);
  gtk_box_append(GTK_BOX(titleBox), subtitleText);

  // Since GTK 4, we need to manually add a title widget if we need/want it,
  // because there's no longer `title` and `subtitle` properties
  gtk_header_bar_set_title_widget(GTK_HEADER_BAR(headerBar), titleBox);
  gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(headerBar), TRUE);
}