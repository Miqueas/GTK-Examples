#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.RadioButton";
const gchar *appTitle = "GtkRadioButton";

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
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *radioButton1 = gtk_radio_button_new_with_label(NULL, "Option 1");
  GtkWidget *radioButton2 = gtk_radio_button_new_with_label_from_widget(
    GTK_RADIO_BUTTON(radioButton1),
    "Option 2"
  );
  GtkWidget *radioButton3 = gtk_radio_button_new_with_label_from_widget(
    GTK_RADIO_BUTTON(radioButton1),
    "Option 3"
  );

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), radioButton1, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), radioButton2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), radioButton3, FALSE, FALSE, 0);
  gtk_widget_show_all(box);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
}