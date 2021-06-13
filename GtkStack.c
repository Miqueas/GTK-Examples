#include <gtk/gtk.h>

void app_activate(GtkApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.c-gtk-examples.GtkStack",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GtkApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    NULL
  );

  GtkWidget *stack = g_object_new(
    GTK_TYPE_STACK,
    "visible", TRUE,
    "transition-type", GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT,
    NULL
  );

  gtk_stack_add_titled(
    GTK_STACK(stack),
    g_object_new(
      GTK_TYPE_LABEL,
      "visible", TRUE,
      "label", "Sexo 1",
      NULL
    ),
    "label1",
    "Label 1"
  );

  gtk_stack_add_titled(
    GTK_STACK(stack),
    g_object_new(
      GTK_TYPE_LABEL,
      "visible", TRUE,
      "label", "Sexo 2",
      NULL
    ),
    "label2",
    "Label 2"
  );

  GtkWidget *switcher = g_object_new(
    GTK_TYPE_STACK_SWITCHER,
    "visible", TRUE,
    "stack", stack,
    NULL
  );

  gtk_header_bar_set_custom_title(GTK_HEADER_BAR(header), switcher);
  gtk_container_add(GTK_CONTAINER(win), stack);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}