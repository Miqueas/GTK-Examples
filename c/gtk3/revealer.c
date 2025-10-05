#include <gtk/gtk.h>

// `GtkRevealer` is a container which animates the transition of its child from
// invisible to visible.

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
void on_clicked(GtkButton* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Revealer";
const static gchar* APP_TITLE = "GtkRevealer";

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
  GtkWidget* revealer = gtk_revealer_new();
  GtkWidget* button = gtk_button_new_with_label("Toggle Revealer");
  GtkWidget* label = gtk_label_new("Revealed Content");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), revealer, TRUE, TRUE, 0);
  gtk_widget_show_all(box);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);

  gtk_container_add(GTK_CONTAINER(revealer), label);
  gtk_revealer_set_transition_type(
    GTK_REVEALER(revealer),
    GTK_REVEALER_TRANSITION_TYPE_CROSSFADE
  );
  gtk_revealer_set_transition_duration(GTK_REVEALER(revealer), 150);

  g_signal_connect(button, "clicked", G_CALLBACK(on_clicked), revealer);

  gtk_widget_show(label);
}

void on_clicked(GtkButton* self, gpointer data) {
  GtkRevealer* revealer = GTK_REVEALER(data);
  gtk_revealer_set_reveal_child(
    revealer,
    !gtk_revealer_get_reveal_child(revealer)
  );
}