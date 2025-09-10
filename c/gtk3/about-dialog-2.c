#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AboutDialog";
const gchar *APP_TITLE = "GtkAboutDialog";
const gchar *AUTHORS[1] = { "Josué Martínez\0" };
const gchar *ARTISTS[1] = { "Josué Martínez\0" };
const gchar *DOCUMENTERS[1] = { "Josué Martínez\0" };
const gchar *TRANSLATOR_CREDITS = "Josué Martínez\0";
const gchar *COMMENTS = "GTK+ 3.0 AboutDialog Example";
const gchar *COPYRIGHT = "Copyright © 2021-2025 Josué Martínez\0";
const gchar *VERSION = "0.1.0";
const gchar *WEBSITE = "https://github.com/Miqueas/GTK-Examples\0";
const gchar *WEBSITE_TEXT = "GitHub Repository\0";
const gchar *LICENSE = "Copyright (C) 2021-2025 Josué Martínez\n"
"\n"
"  This software is provided 'as-is', without any express or implied\n"
"  warranty.  In no event will the authors be held liable for any damages\n"
"  arising from the use of this software.\n"
"\n"
"  Permission is granted to anyone to use this software for any purpose,\n"
"  including commercial applications, and to alter it and redistribute it\n"
"  freely, subject to the following restrictions:\n"
"\n"
"  1. The origin of this software must not be misrepresented; you must not\n"
"     claim that you wrote the original software. If you use this software\n"
"     in a product, an acknowledgment in the product documentation would be\n"
"     appreciated but is not required.\n"
"  2. Altered source versions must be plainly marked as such, and must not be\n"
"     misrepresented as being the original software.\n"
"  3. This notice may not be removed or altered from any source distribution.\0"
;

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);

  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);

  gtk_show_about_dialog(window,
    "modal", TRUE,
    "artists", ARTISTS,
    "authors", AUTHORS,
    "documenters", DOCUMENTERS,
    "translator-credits", TRANSLATOR_CREDITS,
    "program-name", APP_TITLE,
    "comments", COMMENTS,
    "copyright", COPYRIGHT,
    "version", VERSION,
    "license", LICENSE,
    "wrap-license", TRUE,
    "website", WEBSITE,
    "website-label", WEBSITE_TEXT,
    "destroy-with-parent", TRUE,
    NULL
  );
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *label;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  label = gtk_label_new("Just an empty window");

  gtk_container_add(GTK_CONTAINER(window), label);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_widget_set_visible(label, TRUE);
}