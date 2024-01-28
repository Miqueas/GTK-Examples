#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.FlowBox";
const gchar *appTitle = "GtkFlowBox";
const gchar *icons[20] = {
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

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *flowBox, *scrolledWindow;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  flowBox = gtk_flow_box_new();
  scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_container_add(GTK_CONTAINER(window), scrolledWindow);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flowBox), GTK_SELECTION_NONE);
  gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flowBox), 30);

  srand(time(NULL));

  for (int i = 0; i < 1000; i++)
    gtk_flow_box_insert(
      GTK_FLOW_BOX(flowBox),
      gtk_image_new_from_icon_name(icons[(rand() % 20)], GTK_ICON_SIZE_DIALOG),
      i
    );

  gtk_container_add(GTK_CONTAINER(scrolledWindow), flowBox);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_widget_show_all(scrolledWindow);
}