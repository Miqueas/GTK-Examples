#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void btn_clicked(GtkButton *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.ListBox";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

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
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", GTK_APPLICATION(self),
    "default-width", 400,
    "default-height", 400,
    "border-width", 10,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkLabel",
    NULL
  );

  GtkWidget *box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "spacing", 10,
    NULL
  );

  GtkWidget *listbox = g_object_new(
    GTK_TYPE_LIST_BOX,
    "visible", TRUE,
    NULL
  );

  GtkWidget *scroll = g_object_new(
    GTK_TYPE_SCROLLED_WINDOW,
    "visible", TRUE,
    "shadow-type", GTK_SHADOW_NONE,
    "propagate-natural-width", TRUE,
    "propagate-natural-height", TRUE,
    NULL
  );

  GtkWidget *btn = g_object_new(
    GTK_TYPE_BUTTON,
    "visible", TRUE,
    "label", "Load",
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  g_signal_connect(btn, "clicked", G_CALLBACK(btn_clicked), listbox);
  gtk_container_add(GTK_CONTAINER(scroll), listbox);
  gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

void btn_clicked(GtkButton *self, gpointer data) {
  for (int i = 0; i < 100; i++) {
    char str[16];
    sprintf(str, "Some text %d", (i + 1));
    gtk_list_box_insert(GTK_LIST_BOX(data), g_object_new(
      GTK_TYPE_LABEL,
      "visible", TRUE,
      "label", str,
      NULL
    ), i);
  }
}