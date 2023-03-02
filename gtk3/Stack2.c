#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
GtkWidget* build_stack();

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkStack2";
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
  GtkWidget *win, *header, *stack, *sidebar, *box;

  win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkStack",
    "subtitle", "GtkStack with GtkStackSidebar example",
    NULL
  );

  stack = build_stack();

  sidebar = g_object_new(
    GTK_TYPE_STACK_SIDEBAR,
    "visible", TRUE,
    "stack", stack,
    "halign", GTK_ALIGN_CENTER,
    NULL
  );
  
  box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_HORIZONTAL,
    "spacing", 10,
    "homogeneous", FALSE,
    NULL
  );

  gtk_box_pack_start(GTK_BOX(box), sidebar, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), stack, TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

GtkWidget* build_stack() {
  GtkWidget *stack = g_object_new(
    GTK_TYPE_STACK,
    "visible", TRUE,
    "transition-type", GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT,
    NULL
  );

  for (int i = 0; i < 3; i++) {
    char label[56], title[7], name[6];

    sprintf(label, "<span size='xx-large' font_weight='bold'>Page %d</span>", i + 1);
    sprintf(title, "Page %d", i + 1);
    sprintf(name, "page%d", i + 1);

    gtk_stack_add_titled(
      GTK_STACK(stack),
      g_object_new(
        GTK_TYPE_LABEL,
        "visible", TRUE,
        "label", label,
        "use-markup", TRUE,
        NULL
      ),
      name,
      title
    );
  }

  return stack;
}