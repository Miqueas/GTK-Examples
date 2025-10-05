#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_check_menu_item_toggle(GtkCheckMenuItem* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.CheckMenuItem";
const static gchar* APP_TITLE = "GtkCheckMenuItem";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);
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
  GtkWidget* menu_bar = gtk_menu_bar_new();
  GtkWidget* file_menu_item = gtk_menu_item_new_with_label("File");
  GtkWidget* file_menu = gtk_menu_new();
  GtkWidget* check_menu_item = gtk_check_menu_item_new_with_label("My option");

  gtk_container_add(GTK_CONTAINER(window), menu_bar);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_show(menu_bar);
  gtk_widget_set_halign(menu_bar, GTK_ALIGN_START);
  gtk_widget_set_valign(menu_bar, GTK_ALIGN_START);
  gtk_container_add(GTK_CONTAINER(menu_bar), file_menu_item);

  gtk_widget_show(file_menu_item);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);

  gtk_widget_show(file_menu);
  gtk_container_add(GTK_CONTAINER(file_menu), check_menu_item);

  gtk_widget_show(check_menu_item);
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(check_menu_item), TRUE);
  g_signal_connect(
    check_menu_item,
    "toggled",
    G_CALLBACK(on_check_menu_item_toggle),
    NULL
  );
}

static void on_check_menu_item_toggle(GtkCheckMenuItem* self, gpointer data) {
  gboolean active = gtk_check_menu_item_get_active(self);
  g_print("Active: %s\n", active ? "Yes" : "No");
}