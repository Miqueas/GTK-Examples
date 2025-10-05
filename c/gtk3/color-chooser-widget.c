#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_show_editor_toggled(GtkToggleButton* self, gpointer data);
static void on_print_clicked(GtkButton* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AppChooserWidget";
const static gchar* APP_TITLE = "GtkAppChooserWidget";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* color_chooser_widget = gtk_color_chooser_widget_new();
  GtkWidget* show_editor_check_button = gtk_check_button_new_with_label("Show editor");
  GtkWidget* print_button = gtk_button_new_with_label("Print Color");
  gboolean show_editor;

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), color_chooser_widget, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), show_editor_check_button, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), print_button, FALSE, FALSE, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_show_all(box);

  g_object_get(G_OBJECT(color_chooser_widget), "show-editor", &show_editor, NULL);

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(show_editor_check_button),
    show_editor
  );

  g_signal_connect(
    show_editor_check_button,
    "toggled",
    G_CALLBACK(on_show_editor_toggled),
    color_chooser_widget
  );

  g_signal_connect(
    print_button,
    "clicked",
    G_CALLBACK(on_print_clicked),
    color_chooser_widget
  );
}

static void on_show_editor_toggled(GtkToggleButton* self, gpointer data) {
  gboolean show_editor = gtk_toggle_button_get_active(self);
  g_object_set(G_OBJECT(data), "show-editor", show_editor, NULL);
}

static void on_print_clicked(GtkButton* self, gpointer data) {
  GdkRGBA color;
  gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(data), &color);
  g_print("Color: %s\n", gdk_rgba_to_string(&color));
}