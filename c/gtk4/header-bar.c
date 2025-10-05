#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.HeaderBar";
const static gchar* APP_TITLE = "<span weight='bold'>GtkHeaderBar</span>";
const static gchar* APP_SUBTITLE = "<span weight='light'>App subtitle</span>";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* title_label = gtk_label_new(APP_TITLE);
  GtkWidget* subtitle_label = gtk_label_new(APP_SUBTITLE);
  GtkWidget* title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget* header_bar = gtk_header_bar_new();

  gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_label_set_use_markup(GTK_LABEL(title_label), TRUE);
  gtk_label_set_use_markup(GTK_LABEL(subtitle_label), TRUE);

  gtk_widget_set_margin_top(title_box, 4);
  gtk_widget_set_margin_bottom(title_box, 4);
  gtk_widget_set_valign(title_box, GTK_ALIGN_CENTER);

  gtk_box_append(GTK_BOX(title_box), title_label);
  gtk_box_append(GTK_BOX(title_box), subtitle_label);

  // Since GTK 4, we need to manually add a title widget because there's no longer `title` and
  // `subtitle` properties
  gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header_bar), title_box);
  gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header_bar), TRUE);
}