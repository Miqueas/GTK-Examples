#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onFontSet(GtkFontButton *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FontButton";
const gchar *APP_TITLE = "GtkFontButton";

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
  GtkWidget *window, *fontButton;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  fontButton = gtk_font_button_new();

  gtk_container_add(GTK_CONTAINER(window), fontButton);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_set_halign(fontButton, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(fontButton, GTK_ALIGN_CENTER);
  gtk_widget_set_visible(fontButton, TRUE);
  gtk_font_button_set_title(GTK_FONT_BUTTON(fontButton), "Pick a font");
  g_signal_connect(fontButton, "font-set", G_CALLBACK(onFontSet), NULL);
}

void onFontSet(GtkFontButton *self, gpointer data) {
  gchar *font = gtk_font_chooser_get_font(GTK_FONT_CHOOSER(self));
  g_print("Font chosen: %s\n", font);
  g_free(font);
}