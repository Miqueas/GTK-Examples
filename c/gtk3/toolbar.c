#include <gtk/gtk.h>

static void on_app_activate(const GApplication* self, gpointer data);
static void on_app_startup(const GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Toolbar";
const static gchar* APP_TITLE = "GtkToolbar";

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
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget* toolbar = gtk_toolbar_new();
  GtkWidget* icon_01 = gtk_image_new_from_icon_name("document-open", GTK_ICON_SIZE_MENU);
  GtkWidget* icon_02 = gtk_image_new_from_icon_name("document-save", GTK_ICON_SIZE_MENU);
  GtkToolItem* button_01 = gtk_tool_button_new(icon_01, NULL);
  GtkToolItem* button_02 = gtk_tool_button_new(icon_02, NULL);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), gtk_label_new("Content Area"), TRUE, TRUE, 0);
  gtk_widget_show_all(box);

  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), button_01, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), button_02, -1);
  gtk_widget_show_all(toolbar);
}