#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onCopyClicked(GtkButton *self, gpointer data);
void onSetClicked(GtkButton *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Clipboard";
const gchar *appTitle = "GtkClipboard";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
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
  GtkWidget *window, *box, *entry, *buttonBox, *copyButton, *setButton;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  entry = gtk_entry_new();
  buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  copyButton = gtk_button_new_with_label("Copy to Clipboard");
  setButton = gtk_button_new_with_label("Set from Clipboard");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), buttonBox, FALSE, FALSE, 0);

  gtk_box_set_spacing(GTK_BOX(buttonBox), 10);
  gtk_box_pack_start(GTK_BOX(buttonBox), copyButton, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(buttonBox), setButton, FALSE, FALSE, 0);
  gtk_button_box_set_layout(GTK_BUTTON_BOX(buttonBox), GTK_BUTTONBOX_CENTER);

  g_signal_connect(copyButton, "clicked", G_CALLBACK(onCopyClicked), entry);
  g_signal_connect(setButton, "clicked", G_CALLBACK(onSetClicked), entry);

  gtk_widget_show_all(box);
}

void onCopyClicked(GtkButton *self, gpointer data) {
  GtkEntry *entry = GTK_ENTRY(data);
  GdkDisplay *display = gdk_display_get_default();
  GtkClipboard *clipboard = gtk_clipboard_get_default(display);
  const gchar *text = gtk_entry_get_text(entry);
  gtk_clipboard_set_text(clipboard, text, -1);
  gtk_widget_grab_focus(GTK_WIDGET(entry));
}

void onSetClicked(GtkButton *self, gpointer data) {
  GtkEntry *entry = GTK_ENTRY(data);
  GdkDisplay *display = gdk_display_get_default();
  GtkClipboard *clipboard = gtk_clipboard_get_default(display);
  const gchar *text = gtk_clipboard_wait_for_text(clipboard);
  gtk_entry_set_text(entry, text);
  gtk_widget_grab_focus(GTK_WIDGET(entry));
}