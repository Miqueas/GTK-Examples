#include <gtk/gtk.h>

// `GtkPaned` a dual child widget that allows user to resize the panes by
// presenting it's children in parallel with a thin draggable divider in the
// middle

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Paned";
const gchar *APP_TITLE = "GtkPaned";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);
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
  GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  GtkWidget *leftLabel = gtk_label_new("Left Pane");
  GtkWidget *rightLabel = gtk_label_new("Right Pane");

  gtk_container_add(GTK_CONTAINER(window), paned);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_size_request(leftLabel, 200, -1);
  gtk_widget_set_size_request(rightLabel, 200, -1);

  gtk_paned_add1(GTK_PANED(paned), leftLabel);
  gtk_paned_add2(GTK_PANED(paned), rightLabel);
  gtk_widget_show_all(paned);
}