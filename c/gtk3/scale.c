#include <gtk/gtk.h>

// `GtkScale` is a slider control used to select a numeric value within a range

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Scale";
const gchar *appTitle = "GtkScale";

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
  GtkWidget *scale = gtk_scale_new_with_range(
    GTK_ORIENTATION_HORIZONTAL,
    0.0, // Minimum value
    100.0, // Maximum value
    1.0 // Step increment
  );

  gtk_container_add(GTK_CONTAINER(window), scale);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(scale);
  gtk_scale_add_mark(GTK_SCALE(scale), 25.0, GTK_POS_BOTTOM, "25");
  gtk_scale_add_mark(GTK_SCALE(scale), 50.0, GTK_POS_BOTTOM, "50");
  gtk_scale_add_mark(GTK_SCALE(scale), 75.0, GTK_POS_BOTTOM, "75");
  gtk_widget_set_valign(scale, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(scale, GTK_ALIGN_CENTER);
  gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
  gtk_widget_set_size_request(scale, 240, -1);
}