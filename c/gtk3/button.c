#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void btn_clicked(GtkButton *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.Button";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win, *btn;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  btn = gtk_button_new_with_label("Click me");

  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  g_object_set(btn, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);

  g_signal_connect(btn, "clicked", G_CALLBACK(btn_clicked), NULL);

  gtk_container_add(GTK_CONTAINER(win), btn);
}

void btn_clicked(GtkButton *self, gpointer data) {
  g_print("You clicked me!\n");
}