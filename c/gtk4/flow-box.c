#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FlowBox";
const static gchar* APP_TITLE = "GtkFlowBox";
const static gchar* ICONS[] = {
  "face-angel\0",
  "face-angry\0",
  "face-surprise\0",
  "face-laugh\0",
  "face-plain\0",
  "face-sad\0",
  "face-cool\0",
  "face-smirk\0",
  "face-sick\0",
  "face-kiss\0",
  "face-heart-broken\0",
  "face-smile\0",
  "face-crying\0",
  "face-devilish\0",
  "face-heart\0",
  "face-sad\0",
  "face-smile-big\0",
  "face-tired\0",
  "face-wink\0",
  "face-worried\0"
};

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup",  G_CALLBACK(on_app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* flow_box = gtk_flow_box_new();
  GtkWidget* scrolled_window = gtk_scrolled_window_new();

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_child(GTK_WINDOW(window), scrolled_window);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flow_box), GTK_SELECTION_NONE);
  gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flow_box), 30);

  for (gint index = 0; index < 1000; index++) {
    gtk_flow_box_insert(
      GTK_FLOW_BOX(flow_box),
      gtk_image_new_from_icon_name(ICONS[g_random_int_range(0, 20)]),
      index
    );
  }

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), flow_box);
  gtk_scrolled_window_set_policy(
    GTK_SCROLLED_WINDOW(scrolled_window),
    GTK_POLICY_NEVER,
    GTK_POLICY_AUTOMATIC
  );
}