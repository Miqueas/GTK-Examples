#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkFlowBox";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", GTK_APPLICATION(self),
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkLabel",
    NULL
  );

  GtkWidget *flowbox = g_object_new(
    GTK_TYPE_FLOW_BOX,
    "visible", TRUE,
    "valign", GTK_ALIGN_START,
    "selection-mode", GTK_SELECTION_NONE,
    "max-children-per-line", 30,
    NULL
  );

  GtkWidget *scroll = g_object_new(
    GTK_TYPE_SCROLLED_WINDOW,
    "visible", TRUE,
    "hscrollbar-policy", GTK_POLICY_NEVER,
    NULL
  );

  char *icons[10] = {
    "face-angry",
    "face-surprise",
    "face-laugh",
    "face-plain",
    "face-sad",
    "face-cool",
    "face-smirk",
    "face-sick",
    "face-kiss",
    "face-smile"
  };

  srand(time(NULL));

  for (int i = 0; i < 400; i++) {
    gtk_flow_box_insert(GTK_FLOW_BOX(flowbox), g_object_new(
      GTK_TYPE_IMAGE,
      "visible", TRUE,
      "icon-name", icons[(rand() % 10)],
      "pixel-size", 32,
      NULL
    ), i);
  }

  gtk_container_add(GTK_CONTAINER(scroll), flowbox);
  gtk_container_add(GTK_CONTAINER(win), scroll);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}