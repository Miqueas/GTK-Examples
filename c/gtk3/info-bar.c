#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onInfoBarResponse(GtkInfoBar *self, int responseID, gpointer data);
void createInfoBar(GtkButton *self, gpointer data);
GtkMessageType stringToGtkMessageType(const gchar *label);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.InfoBar";
const gchar *appTitle = "GtkInfoBar";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, G_APPLICATION_FLAGS_NONE);

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
  GtkWidget *window, *box, *grid, *infoButton, *warningButton, *questionButton, *errorButton, *otherButton;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  grid = gtk_grid_new();
  infoButton = gtk_button_new_with_label("Info");
  warningButton = gtk_button_new_with_label("Warning");
  questionButton = gtk_button_new_with_label("Question");
  errorButton = gtk_button_new_with_label("Error");
  otherButton = gtk_button_new_with_label("Other");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
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

  g_signal_connect(infoButton, "clicked", G_CALLBACK(createInfoBar), box);
  g_signal_connect(warningButton, "clicked", G_CALLBACK(createInfoBar), box);
  g_signal_connect(questionButton, "clicked", G_CALLBACK(createInfoBar), box);
  g_signal_connect(errorButton, "clicked", G_CALLBACK(createInfoBar), box);
  g_signal_connect(otherButton, "clicked", G_CALLBACK(createInfoBar), box);
}

void createInfoBar(GtkButton *self, gpointer data) {
  const gchar *buttonText = gtk_button_get_label(self);
  GtkWidget *infoBar, *infoBarContentBox;

  infoBar = gtk_info_bar_new();
  infoBarContentBox = gtk_info_bar_get_content_area(GTK_INFO_BAR(infoBar));

  gtk_info_bar_set_show_close_button(GTK_INFO_BAR(infoBar), TRUE);
  gtk_info_bar_set_message_type(GTK_INFO_BAR(infoBar), stringToGtkMessageType(buttonText));
  g_signal_connect(infoBar, "response", G_CALLBACK(onInfoBarResponse), data);

  gtk_box_pack_start(GTK_BOX(infoBarContentBox), gtk_label_new(buttonText), FALSE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(data), infoBar, FALSE, TRUE, 0);
  gtk_widget_show_all(GTK_WIDGET(data));
}

void onInfoBarResponse(GtkInfoBar *self, int responseID, gpointer data) {
  gtk_container_remove(GTK_CONTAINER(data), GTK_WIDGET(self));
  gtk_widget_destroy(GTK_WIDGET(self));
}

GtkMessageType stringToGtkMessageType(const gchar *label) {
  GtkMessageType result;
  gchar *string = g_ascii_strup(label, strlen(label));

  if (g_str_equal("INFO", string))
    result = GTK_MESSAGE_INFO;
  else if (g_str_equal("WARNING", string))
    result = GTK_MESSAGE_WARNING;
  else if (g_str_equal("QUESTION", string))
    result = GTK_MESSAGE_QUESTION;
  else if (g_str_equal("ERROR", string))
    result = GTK_MESSAGE_ERROR;
  else if (g_str_equal("OTHER", string))
    result = GTK_MESSAGE_OTHER;

  return result;
}