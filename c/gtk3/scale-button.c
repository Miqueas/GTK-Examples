#include <gtk/gtk.h>

// `GtkScaleButton` is a button that pops up a scale control

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onValueChanged(GtkScaleButton *self, gdouble value, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.ScaleButton";
const gchar *APP_TITLE = "GtkScaleButton";
const gchar *icons[2] = { "zoom-out", "zoom-in" };

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
  GtkWidget *button = gtk_scale_button_new(
    GTK_ICON_SIZE_SMALL_TOOLBAR, // Icon size
    0.0, // Minimum value
    100.0, // Maximum value
    1.0, // Step increment
    icons
  );

  gtk_container_add(GTK_CONTAINER(window), button);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_show(button);
  gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
  g_signal_connect(button, "value-changed", G_CALLBACK(onValueChanged), NULL);
}

void onValueChanged(GtkScaleButton *self, gdouble value, gpointer data) {
  g_print("Scale value: %f\n", value);
}