#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onButtonClicked(GtkButton *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ListBox";
const gchar *appTitle = "GtkListBox";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

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
  GtkWidget *window, *box, *listBox, *scrolledWindow, *button;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  listBox = gtk_list_box_new();
  scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
  button = gtk_button_new_with_label("Load");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_pack_start(GTK_BOX(box), scrolledWindow, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
  gtk_widget_show_all(box);

  gtk_container_add(GTK_CONTAINER(scrolledWindow), listBox);
  gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_SHADOW_NONE);
  gtk_scrolled_window_set_propagate_natural_width(GTK_SCROLLED_WINDOW(scrolledWindow), TRUE);
  gtk_scrolled_window_set_propagate_natural_height(GTK_SCROLLED_WINDOW(scrolledWindow), TRUE);
  gtk_widget_show_all(scrolledWindow);

  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_start(button, 10);
  gtk_widget_set_margin_end(button, 10);
  gtk_widget_set_margin_bottom(button, 10);
  g_signal_connect(button, "clicked", G_CALLBACK(onButtonClicked), listBox);
}

void onButtonClicked(GtkButton *self, gpointer data) {
  for (int i = 0; i < 100; i++) {
    char str[16];
    sprintf(str, "Some text %d", (i + 1));
    GtkWidget *tempLabel = gtk_label_new(str);
    gtk_widget_set_margin_start(tempLabel, 10);
    gtk_widget_set_margin_end(tempLabel, 10);
    gtk_widget_set_margin_top(tempLabel, 10);
    gtk_widget_set_margin_bottom(tempLabel, 10);
    gtk_list_box_insert(GTK_LIST_BOX(data), tempLabel, i);
  }

  gtk_widget_show_all(GTK_WIDGET(data));
}