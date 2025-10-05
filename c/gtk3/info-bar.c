#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
void on_info_bar_response(GtkInfoBar* self, gint responseID, gpointer data);
void build_info_bar(GtkButton* self, gpointer data);
GtkMessageType string_to_gtk_message_type(const gchar* label);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.InfoBar";
const static gchar* APP_TITLE = "GtkInfoBar";

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
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget* grid = gtk_grid_new();
  GtkWidget* infoButton = gtk_button_new_with_label("Info");
  GtkWidget* warningButton = gtk_button_new_with_label("Warning");
  GtkWidget* questionButton = gtk_button_new_with_label("Question");
  GtkWidget* errorButton = gtk_button_new_with_label("Error");
  GtkWidget* otherButton = gtk_button_new_with_label("Other");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_pack_end(GTK_BOX(box), grid, TRUE, TRUE, 0);
  gtk_widget_show_all(box);

  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
  gtk_grid_attach(GTK_GRID(grid), infoButton, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), warningButton, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), questionButton, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), errorButton, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), otherButton, 0, 2, 2, 1);
  gtk_widget_show_all(grid);

  g_signal_connect(infoButton, "clicked", G_CALLBACK(build_info_bar), box);
  g_signal_connect(warningButton, "clicked", G_CALLBACK(build_info_bar), box);
  g_signal_connect(questionButton, "clicked", G_CALLBACK(build_info_bar), box);
  g_signal_connect(errorButton, "clicked", G_CALLBACK(build_info_bar), box);
  g_signal_connect(otherButton, "clicked", G_CALLBACK(build_info_bar), box);
}

void build_info_bar(GtkButton* self, gpointer data) {
  const gchar* buttonText = gtk_button_get_label(self);
  GtkWidget* info_bar = gtk_info_bar_new();
  GtkWidget* info_bar_content_box = gtk_info_bar_get_content_area(GTK_INFO_BAR(info_bar));

  gtk_info_bar_set_show_close_button(GTK_INFO_BAR(info_bar), TRUE);
  gtk_info_bar_set_message_type(GTK_INFO_BAR(info_bar), string_to_gtk_message_type(buttonText));
  g_signal_connect(info_bar, "response", G_CALLBACK(on_info_bar_response), data);

  gtk_box_pack_start(GTK_BOX(info_bar_content_box), gtk_label_new(buttonText), FALSE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(data), info_bar, FALSE, TRUE, 0);
  gtk_widget_show_all(GTK_WIDGET(data));
}

void on_info_bar_response(GtkInfoBar* self, gint responseID, gpointer data) {
  gtk_container_remove(GTK_CONTAINER(data), GTK_WIDGET(self));
  gtk_widget_destroy(GTK_WIDGET(self));
}

GtkMessageType string_to_gtk_message_type(const gchar* label) {
  GtkMessageType result = 0;
  gchar* string = g_utf8_strup(label, g_utf8_strlen(label, 16));

  if (g_str_equal("INFO",     string)) result = GTK_MESSAGE_INFO;
  if (g_str_equal("WARNING",  string)) result = GTK_MESSAGE_WARNING;
  if (g_str_equal("QUESTION", string)) result = GTK_MESSAGE_QUESTION;
  if (g_str_equal("ERROR",    string)) result = GTK_MESSAGE_ERROR;
  if (result == 0)                     result = GTK_MESSAGE_OTHER;

  return result;
}