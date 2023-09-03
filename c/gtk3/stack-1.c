#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
GtkWidget* doStack();

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Stack1";
const gchar *appTitle = "GtkStack";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *win, *stack, *switcher, *box;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  stack = doStack();
  switcher = gtk_stack_switcher_new();
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_title(GTK_WINDOW(win), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(win), 10);

  gtk_widget_set_halign(switcher, GTK_ALIGN_CENTER);
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));

  gtk_box_set_homogeneous(GTK_BOX(box), FALSE);
  gtk_box_pack_start(GTK_BOX(box), stack, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), switcher, FALSE, TRUE, 0);
  gtk_widget_show_all(box);
}

GtkWidget* doStack() {
  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

  for (int i = 0; i < 3; i++) {
    char label[56], title[7], name[6];

    sprintf(label, "<span size='xx-large' font_weight='bold'>Page %d</span>", i + 1);
    sprintf(title, "Page %d", i + 1);
    sprintf(name, "page%d", i + 1);

    GtkWidget *widget = gtk_label_new(label);
    gtk_label_set_use_markup(GTK_LABEL(widget), TRUE);

    gtk_stack_add_titled(GTK_STACK(stack), widget, name, title);
  }

  return stack;
}