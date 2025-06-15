#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onDropDownNotify(GObject* self, GParamSpec* pspec, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk4.DropDown";
const gchar *appTitle = "GtkLabel";
const char *items[9] = {
  "GNOME\0",
  "KDE Plasma\0",
  "XFCE\0",
  "MATE\0",
  "Cinnamon\0",
  "Pantheon\0",
  "LXDE\0",
  "LXQT\0",
  NULL
};

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup",  G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *box, *hintLabel, *dropDown, *selectedLabel;
  GtkStringList *list;

  list = gtk_string_list_new(items);
  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  dropDown = gtk_drop_down_new(G_LIST_MODEL(list), NULL);
  hintLabel = gtk_label_new("Select an option");
  selectedLabel = gtk_label_new("Selected: None");

  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_box_append(GTK_BOX(box), hintLabel);
  gtk_box_append(GTK_BOX(box), dropDown);
  gtk_box_append(GTK_BOX(box), selectedLabel);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  g_signal_connect(
    dropDown,
    "notify::selected",
    G_CALLBACK(onDropDownNotify),
    selectedLabel
  );
}

void onDropDownNotify(GObject* self, GParamSpec* pspec, gpointer data) {
  GtkLabel *selectedLabel = GTK_LABEL(data);
  GtkDropDown *dropDown = GTK_DROP_DOWN(self);
  GtkStringList *list = GTK_STRING_LIST(gtk_drop_down_get_model(dropDown));
  guint selected = gtk_drop_down_get_selected(dropDown);
  const gchar *selectedValue = gtk_string_list_get_string(list, selected);
  const gchar *selectedText = g_strconcat("Selected: ", selectedValue, NULL);
  g_print("%s\n", selectedText);
  gtk_label_set_label(selectedLabel, selectedText);
}