#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void create_info_bar(GtkButton *self, gpointer data);
void info_bar_on_response(GtkInfoBar *self, int res_id, gpointer data);
GtkMessageType str_to_msg_type(const gchar *label);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkInfoBar";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  GtkWidget *box, *grid, *info_btn, *warning_btn, *question_btn, *error_btn, *other_btn;

  box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    NULL
  );

  grid = g_object_new(
    GTK_TYPE_GRID,
    "visible", TRUE,
    "column-homogeneous", TRUE,
    "row-homogeneous", TRUE,
    "column-spacing", 10,
    "row-spacing", 10,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  gtk_box_pack_end(GTK_BOX(box), grid, TRUE, TRUE, 0);

  info_btn     = g_object_new(GTK_TYPE_BUTTON, "visible", TRUE, "label", "Info", NULL);
  warning_btn  = g_object_new(GTK_TYPE_BUTTON, "visible", TRUE, "label", "Warning", NULL);
  question_btn = g_object_new(GTK_TYPE_BUTTON, "visible", TRUE, "label", "Question", NULL);
  error_btn    = g_object_new(GTK_TYPE_BUTTON, "visible", TRUE, "label", "Error", NULL);
  other_btn    = g_object_new(GTK_TYPE_BUTTON, "visible", TRUE, "label", "Other", NULL);

  g_signal_connect(info_btn, "clicked", G_CALLBACK(create_info_bar), box);
  g_signal_connect(warning_btn, "clicked", G_CALLBACK(create_info_bar), box);
  g_signal_connect(question_btn, "clicked", G_CALLBACK(create_info_bar), box);
  g_signal_connect(error_btn, "clicked", G_CALLBACK(create_info_bar), box);
  g_signal_connect(other_btn, "clicked", G_CALLBACK(create_info_bar), box);

  //                                            L  T  W  H
  gtk_grid_attach(GTK_GRID(grid), info_btn,     0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), warning_btn,  1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), question_btn, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), error_btn,    1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), other_btn,    0, 2, 2, 1);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "default-height", 400,
    "border-width", 10,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "My App",
    "subtitle", "An awesome app that you'll love",
    NULL
  );

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

void create_info_bar(GtkButton *self, gpointer data) {
  GtkWidget *info_bar = g_object_new(
    GTK_TYPE_INFO_BAR,
    "visible", TRUE,
    "message-type", str_to_msg_type(gtk_button_get_label(self)),
    "show-close-button", TRUE,
    NULL
  );

  gtk_box_pack_start(
    GTK_BOX(gtk_info_bar_get_content_area(GTK_INFO_BAR(info_bar))),
    g_object_new(
      GTK_TYPE_LABEL,
      "visible", TRUE,
      "label", gtk_button_get_label(self),
      NULL
    ), FALSE, TRUE, 0
  );

  g_signal_connect(info_bar, "response", G_CALLBACK(info_bar_on_response), data);

  gtk_box_pack_start(GTK_BOX(data), info_bar, FALSE, TRUE, 0);
}

void info_bar_on_response(GtkInfoBar *self, int res_id, gpointer data) {
  gtk_container_remove(GTK_CONTAINER(data), GTK_WIDGET(self));
  gtk_widget_destroy(GTK_WIDGET(self));
}

GtkMessageType str_to_msg_type(const gchar *label) {
  GtkMessageType ret;
  gchar *name = g_ascii_strup(label, strlen(label));

  if (g_str_equal("INFO", name))
    ret = GTK_MESSAGE_INFO;
  else if (g_str_equal("WARNING", name))
    ret = GTK_MESSAGE_WARNING;
  else if (g_str_equal("QUESTION", name))
    ret = GTK_MESSAGE_QUESTION;
  else if (g_str_equal("ERROR", name))
    ret = GTK_MESSAGE_ERROR;
  else if (g_str_equal("OTHER", name))
    ret = GTK_MESSAGE_OTHER;

  return ret;
}