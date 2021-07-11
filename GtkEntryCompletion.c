#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

char *items[6] = { "GNOME", "C", "GTK", "Example", "Hello, world!" };

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.c-gtk-examples.GtkEntryCompletion",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));

  GtkListStore *model = gtk_list_store_new(1, G_TYPE_STRING);
  GtkTreeIter iter;

  for (int i = 0; i < 6; i++) {
    gtk_list_store_append(model, &iter);
    gtk_list_store_set(model, &iter, 0, items[i], -1);
  }

  GtkEntryCompletion *completion = gtk_entry_completion_new();
  gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(model));
  gtk_entry_completion_set_text_column(completion, 0);

  GtkWidget *entry = g_object_new(
    GTK_TYPE_ENTRY,
    "visible", TRUE,
    "completion", completion,
    NULL
  );

  GtkWidget *box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "spacing", 10,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  GtkWidget *hint_label = g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "Try input \"gnome\" or \"hello\"",
    NULL
  );

  gtk_box_pack_start(GTK_BOX(box), hint_label, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(win), box);
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
    "title", "GtkEntry",
    "subtitle", "Example 1",
    NULL
  );

  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}