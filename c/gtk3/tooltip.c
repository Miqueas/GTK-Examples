#include <gtk/gtk.h>

static void on_app_activate(const GApplication* self, gpointer data);
static void on_app_startup(const GApplication* self, gpointer data);
static gboolean on_button_03_query_tooltip(
  GtkWidget* self,
  gint x,
  gint y,
  gboolean keyboard_mode,
  GtkTooltip* tooltip,
  gpointer data
);
static gboolean on_button_04_query_tooltip(
  GtkWidget* self,
  gint x,
  gint y,
  gboolean keyboard_mode,
  GtkTooltip* tooltip,
  gpointer data
);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Tooltip";
const static gchar* APP_TITLE = "GtkTooltip";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(const GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(const GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* label = gtk_label_new("Hover the buttons to see the tooltips");
  GtkWidget* button_01 = gtk_button_new_with_label("Button 01");
  GtkWidget* button_02 = gtk_button_new_with_label("Button 02");
  GtkWidget* button_03 = gtk_button_new_with_label("Button 03");
  GtkWidget* button_04 = gtk_button_new_with_label("Button 04");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), button_01, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), button_02, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), button_03, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), button_04, FALSE, FALSE, 0);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_box_set_homogeneous(GTK_BOX(box), FALSE);
  gtk_widget_show_all(box);

  gtk_widget_set_has_tooltip(button_01, TRUE);
  gtk_widget_set_tooltip_text(button_01, "This is button 01");

  gtk_widget_set_has_tooltip(button_02, TRUE);
  gtk_widget_set_tooltip_markup(button_02, "<span font='Bold 16'>This is button 02</span>");

  gtk_widget_set_has_tooltip(button_03, TRUE);
  g_signal_connect(button_03, "query-tooltip", G_CALLBACK(on_button_03_query_tooltip), NULL);

  gtk_widget_set_has_tooltip(button_04, TRUE);
  g_signal_connect(button_04, "query-tooltip", G_CALLBACK(on_button_04_query_tooltip), NULL);
}

static gboolean on_button_03_query_tooltip(
  GtkWidget* self,
  gint x,
  gint y,
  gboolean keyboard_mode,
  GtkTooltip* tooltip,
  gpointer data
) {
  gtk_tooltip_set_icon_from_icon_name(tooltip, "emblem-important", GTK_ICON_SIZE_BUTTON);
  gtk_tooltip_set_markup(tooltip, "<span font='Bold'>This is button 03</span>");
  return TRUE;
}

static gboolean on_button_04_query_tooltip(
  GtkWidget* self,
  gint x,
  gint y,
  gboolean keyboard_mode,
  GtkTooltip* tooltip,
  gpointer data
) {
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget* title = gtk_label_new("<span font='Bold 16'>This is button 04</span>");
  GtkWidget* description = gtk_label_new(
    "This a much more complex tooltip.\n"
    "For this example tooltip, we have\n"
    "an icon, a title and a description."
  );

  gtk_label_set_use_markup(GTK_LABEL(title), TRUE);

  gtk_box_pack_start(GTK_BOX(box), title, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), description, FALSE, FALSE, 0);
  gtk_widget_show_all(box);

  gtk_tooltip_set_icon_from_icon_name(tooltip, "emblem-important", GTK_ICON_SIZE_BUTTON);
  gtk_tooltip_set_custom(tooltip, box);

  return TRUE;
}