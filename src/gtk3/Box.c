#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void btn_clicked(GtkButton *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkBox";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
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
  GtkWidget *win, *header, *box, *label, *btn;

  win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", GTK_APPLICATION(self),
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkBox",
    NULL
  );

  box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "spacing", 10,
    "homogeneous", FALSE,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  label = g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "Click the button",
    NULL
  );

  btn = g_object_new(
    GTK_TYPE_BUTTON,
    "visible", TRUE,
    "label", "🤔",
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  g_signal_connect(btn, "clicked", G_CALLBACK(btn_clicked), NULL);

  gtk_box_pack_start(GTK_BOX(box), label, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), btn, FALSE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

void btn_clicked(GtkButton *self, gpointer data) {
  static int count = 0;
  g_print("You clicked %d times!\n", ++count);
}