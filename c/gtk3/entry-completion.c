#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.EntryCompletion";
const static gchar* APP_TITLE = "GtkEntryCompletion";
const gchar* items[6] = { "GNOME", "C", "GTK", "Example", "Hello, world!" };

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
  GtkListStore* model = gtk_list_store_new(1, G_TYPE_STRING);
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* entry = gtk_entry_new();
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* hintLabel = gtk_label_new("Try typing \"gnome\" or \"hello\"");
  GtkEntryCompletion* completion = gtk_entry_completion_new();
  GtkTreeIter iter;

  for (gint i = 0; i < 6; i++) {
    gtk_list_store_append(model, &iter);
    gtk_list_store_set(model, &iter, 0, items[i], -1);
  }

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_add(GTK_CONTAINER(window), box);

  gtk_entry_set_completion(GTK_ENTRY(entry), completion);

  gtk_widget_show_all(box);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(box), hintLabel, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, TRUE, 0);

  gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(model));
  gtk_entry_completion_set_text_column(completion, 0);
}