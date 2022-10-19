#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void btn_clicked(GtkButton *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK-Examples.Gtk3.Box";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup", G_CALLBACK(app_startup),  NULL);
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
  GtkWidget *win, *box, *label, *btn;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  label = gtk_label_new("Click the button");
  btn = gtk_button_new_with_label("🤔");

  GtkWidget *widgets[3] = { box, label, btn };

  for (int i = 0; i < 3; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  g_object_set(box, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);
  g_object_set(btn, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);

  g_signal_connect(btn, "clicked", G_CALLBACK(btn_clicked), NULL);

  gtk_box_pack_start(GTK_BOX(box), label, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), btn, FALSE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(win), box);
}

void btn_clicked(GtkButton *self, gpointer data) {
  static int count = 0;
  g_print("You clicked %d times!\n", ++count);
}