#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
GtkWidget* buildStack();

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Stack2";
const gchar *appTitle = "GtkStack";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

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
  GtkWidget *win, *stack, *sidebar, *box;

  win = gtk_application_window_new(GTK_APPLICATION(self));
  stack = buildStack();
  sidebar = gtk_stack_sidebar_new();
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

  gtk_window_set_child(GTK_WINDOW(win), box);
  gtk_window_set_title(GTK_WINDOW(win), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

  gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));

  gtk_box_append(GTK_BOX(box), sidebar);
  gtk_box_append(GTK_BOX(box), stack);
}

GtkWidget* buildStack() {
  GtkWidget *stack = gtk_stack_new();
  gtk_widget_set_vexpand(stack, TRUE);
  gtk_widget_set_hexpand(stack, TRUE);
  gtk_stack_set_transition_type(
    GTK_STACK(stack),
    GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN
  );

  for (int i = 0; i < 3; i++) {
    char label[56], title[7], name[6];

    sprintf(
      label,
      "<span size='xx-large' font_weight='bold'>Page %d</span>",
      i + 1
    );
    sprintf(title, "Page %d", i + 1);
    sprintf(name, "page%d", i + 1);

    GtkWidget *widget = gtk_label_new(label);
    gtk_label_set_use_markup(GTK_LABEL(widget), TRUE);

    gtk_stack_add_titled(GTK_STACK(stack), widget, name, title);
  }

  return stack;
}