#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
GtkWidget* buildStack();

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Stack1";
const static gchar* APP_TITLE = "GtkStack";

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
  GtkWidget* window, *stack, *switcher, *box;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  stack = buildStack();
  switcher = gtk_stack_switcher_new();
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_halign(switcher, GTK_ALIGN_CENTER);
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));

  gtk_widget_set_margin_top(box, 10);
  gtk_widget_set_margin_end(box, 10);
  gtk_widget_set_margin_bottom(box, 10);
  gtk_widget_set_margin_start(box, 10);
  gtk_box_append(GTK_BOX(box), stack);
  gtk_box_append(GTK_BOX(box), switcher);
}

GtkWidget* buildStack() {
  GtkWidget* stack = gtk_stack_new();
  gtk_widget_set_vexpand(stack, TRUE);
  gtk_widget_set_hexpand(stack, TRUE);
  gtk_stack_set_transition_type(
    GTK_STACK(stack),
    GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT
  );

  for (gint i = 0; i < 3; i++) {
    gchar label[70], title[20], name[20];

    sprintf(
      label,
      "<span size='xx-large' font_weight='bold'>Page %d</span>",
      i + 1
    );

    sprintf(title, "Page %d", i + 1);
    sprintf(name, "page%d", i + 1);

    GtkWidget* widget = gtk_label_new(label);
    gtk_label_set_use_markup(GTK_LABEL(widget), TRUE);

    gtk_stack_add_titled(GTK_STACK(stack), widget, name, title);
  }

  return stack;
}