#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FlowBox";
const static gchar* APP_TITLE = "GtkFlowBox";
const static gchar* icons[20] = {
  "face-angel",
  "face-angry",
  "face-surprise",
  "face-laugh",
  "face-plain",
  "face-sad",
  "face-cool",
  "face-smirk",
  "face-sick",
  "face-kiss",
  "face-heart-broken",
  "face-smile",
  "face-crying",
  "face-devilish",
  "face-heart",
  "face-sad",
  "face-smile-big",
  "face-tired",
  "face-wink",
  "face-worried"
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
  GtkWidget* window, *flowBox, *scrolledWindow;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  flowBox = gtk_flow_box_new();
  scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_container_add(GTK_CONTAINER(window), scrolledWindow);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flowBox), GTK_SELECTION_NONE);
  gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flowBox), 30);

  srand(time(NULL));

  for (gint i = 0; i < 1000; i++)
    gtk_flow_box_insert(
      GTK_FLOW_BOX(flowBox),
      gtk_image_new_from_icon_name(icons[(rand() % 20)], GTK_ICON_SIZE_DIALOG),
      i
    );

  gtk_container_add(GTK_CONTAINER(scrolledWindow), flowBox);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_widget_show_all(scrolledWindow);
}