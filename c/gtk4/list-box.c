#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_button_clicked(GtkButton* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ListBox";
const static gchar* APP_TITLE = "GtkListBox";

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
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* list_box = gtk_list_box_new();
  GtkWidget* scrolled_window = gtk_scrolled_window_new();
  GtkWidget* button = gtk_button_new_with_label("Load");

  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_append(GTK_BOX(box), scrolled_window);
  gtk_box_append(GTK_BOX(box), button);

  gtk_widget_set_vexpand(list_box, TRUE);

  gtk_widget_set_vexpand(scrolled_window, TRUE);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), list_box);
  gtk_scrolled_window_set_propagate_natural_width(
    GTK_SCROLLED_WINDOW(scrolled_window),
    TRUE
  );
  gtk_scrolled_window_set_propagate_natural_height(
    GTK_SCROLLED_WINDOW(scrolled_window),
    TRUE
  );

  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_start(button, 10);
  gtk_widget_set_margin_end(button, 10);
  gtk_widget_set_margin_bottom(button, 10);
  g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), list_box);
}

void on_button_clicked(GtkButton* self, gpointer data) {
  for (gint i = 0; i < 1000; i++) {
    gchar str[16];
    sprintf(str, "Item %d", (i + 1));
    GtkWidget* temp_label = gtk_label_new(str);
    gtk_widget_set_margin_start(temp_label, 10);
    gtk_widget_set_margin_end(temp_label, 10);
    gtk_widget_set_margin_top(temp_label, 10);
    gtk_widget_set_margin_bottom(temp_label, 10);
    gtk_list_box_insert(GTK_LIST_BOX(data), temp_label, i);
  }
}