#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onShowEditorToggled(GtkToggleButton *self, gpointer data);
void onPrintClicked(GtkButton *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AppChooserWidget";
const gchar *APP_TITLE = "GtkAppChooserWidget";

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
  gboolean showEditor;
  GtkWidget *window, *box, *colorChooserWidget, *showEditorCheckButton,
    *printButton;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  colorChooserWidget = gtk_color_chooser_widget_new();
  showEditorCheckButton = gtk_check_button_new_with_label("Show editor");
  printButton = gtk_button_new_with_label("Print Color");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), colorChooserWidget, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), showEditorCheckButton, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), printButton, FALSE, FALSE, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_show_all(box);

  g_object_get(G_OBJECT(colorChooserWidget), "show-editor", &showEditor, NULL);

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(showEditorCheckButton),
    showEditor
  );

  g_signal_connect(
    showEditorCheckButton,
    "toggled",
    G_CALLBACK(onShowEditorToggled),
    colorChooserWidget
  );

  g_signal_connect(
    printButton,
    "clicked",
    G_CALLBACK(onPrintClicked),
    colorChooserWidget
  );
}

void onShowEditorToggled(GtkToggleButton *self, gpointer data) {
  gboolean showEditor = gtk_toggle_button_get_active(self);
  g_object_set(G_OBJECT(data), "show-editor", showEditor, NULL);
}

void onPrintClicked(GtkButton *self, gpointer data) {
  GdkRGBA color;
  gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(data), &color);
  g_print("Color: %s\n", gdk_rgba_to_string(&color));
}