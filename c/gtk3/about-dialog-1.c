#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AboutDialog";
const gchar *appTitle = "GtkAboutDialog";
const gchar *authors[1] = { "Josué Martínez\0" };
const gchar *artists[1] = { "Josué Martínez\0" };
const gchar *documenters[1] = { "Josué Martínez\0" };
const gchar *translatorCredits = "Josué Martínez\0";
const gchar *comments = "GTK+ 3.0 AboutDialog Example";
const gchar *copyright = "Copyright © 2021-2025 Josué Martínez\0";
const gchar *version = "0.1.0";
const gchar *website = "https://github.com/Miqueas/GTK-Examples\0";
const gchar *websiteLabel = "GitHub Repository\0";
const gchar *license = "Copyright (C) 2021-2025 Josué Martínez\n"
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
  GtkApplication *app = gtk_application_new(appID, 0);

  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_dialog_run(GTK_DIALOG(window));
  gtk_widget_destroy(GTK_WIDGET(window));
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *dialog;

  dialog = gtk_about_dialog_new();

  gtk_window_set_application(GTK_WINDOW(dialog), GTK_APPLICATION(self));
  gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
  gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(dialog), artists);
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
  gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(dialog), documenters);
  gtk_about_dialog_set_translator_credits(
    GTK_ABOUT_DIALOG(dialog),
    translatorCredits
  );
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), appTitle);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), comments);
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), copyright);
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), version);
  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog), license);
  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(dialog), TRUE);
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), website);
  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog), websiteLabel);
}