#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.EntryCompletion";
const gchar *APP_TITLE = "GtkEntryCompletion";
const char *items[6] = { "GNOME", "C", "GTK", "Example", "Hello, world!" };

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);

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
  GtkListStore *model;
  GtkTreeIter iter;
  GtkWidget *window, *entry, *box, *hintLabel;
  GtkEntryCompletion *completion;

  model = gtk_list_store_new(1, G_TYPE_STRING);
  window = gtk_application_window_new(GTK_APPLICATION(self));
  entry = gtk_entry_new();
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  hintLabel = gtk_label_new("Try typing \"gnome\" or \"hello\"");
  completion = gtk_entry_completion_new();

  GtkWidget* widgets[3] = { entry, box, hintLabel };

  for (int i = 0; i < 3; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  for (int i = 0; i < 6; i++) {
    gtk_list_store_append(model, &iter);
    gtk_list_store_set(model, &iter, 0, items[i], -1);
  }

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_add(GTK_CONTAINER(window), box);

  gtk_entry_set_completion(GTK_ENTRY(entry), completion);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(box), hintLabel, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, TRUE, 0);

  gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(model));
  gtk_entry_completion_set_text_column(completion, 0);
}