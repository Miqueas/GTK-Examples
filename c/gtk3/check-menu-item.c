#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onCheckMenuItemToggle(GtkCheckMenuItem *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.CheckMenuItem";
const gchar *appTitle = "GtkCheckMenuItem";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);
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
  GtkWidget *menuBar = gtk_menu_bar_new();
  GtkWidget *fileMenuItem = gtk_menu_item_new_with_label("File");
  GtkWidget *fileMenu = gtk_menu_new();
  GtkWidget *checkMenuItem = gtk_check_menu_item_new_with_label("My option");

  gtk_container_add(GTK_CONTAINER(window), menuBar);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_show(menuBar);
  gtk_widget_set_halign(menuBar, GTK_ALIGN_START);
  gtk_widget_set_valign(menuBar, GTK_ALIGN_START);
  gtk_container_add(GTK_CONTAINER(menuBar), fileMenuItem);

  gtk_widget_show(fileMenuItem);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMenuItem), fileMenu);

  gtk_widget_show(fileMenu);
  gtk_container_add(GTK_CONTAINER(fileMenu), checkMenuItem);

  gtk_widget_show(checkMenuItem);
  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(checkMenuItem), TRUE);
  g_signal_connect(
    checkMenuItem,
    "toggled",
    G_CALLBACK(onCheckMenuItemToggle),
    NULL
  );
}

void onCheckMenuItemToggle(GtkCheckMenuItem *self, gpointer data) {
  gboolean active = gtk_check_menu_item_get_active(self);
  g_print("Active: %s\n", active ? "Yes" : "No");
}