#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.TextView";
const gchar *appTitle = "GtkTextView";
const gchar *loremIpsum =
"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
"incididunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad"
"sapientiam perveniri potest, non paranda nobis solum ea, sed fruenda etiam"
"sapientia est; sive hoc difficile est, tamen nec modus est ullus investigandi"
"veri, nisi inveneris, et quaerendi defatigatio turpis est, cum id, quod maxime"
"placeat, facere possimus, omnis voluptas assumenda est, omnis."
"\n\n"
"Ut omittam pericula, labores, dolorem etiam, quem optimus quisque pro patria et"
"pro suis suscipit, ut non plus voluptatum habeat quam dolorum. Nam et ipsa"
"declinatio ad libidinem fingitur -- ait enim declinare atomum sine causa; quo."
"\n\n"
"Credo quibusdam usu venire; ut abhorreant a Latinis, quod inciderint in inculta"
"quaedam et quasi architecto beatae vitae dicta sunt, explicabo. Nemo enim ipsam"
"voluptatem, quia voluptas sit, aspernatur aut odit aut fugit, sed quia maiores"
"consequatur. Eadem fortitudinis ratio reperietur. Nam neque laborum perfunctio"
"neque.\0";

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
  GtkWidget *window, *textView;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  textView = gtk_text_view_new();

  gtk_container_add(GTK_CONTAINER(window), textView);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), FALSE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView), GTK_WRAP_WORD);

  GtkTextBuffer *textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
  gtk_text_buffer_set_text(GTK_TEXT_BUFFER(textBuffer), loremIpsum, -1);

  gtk_widget_show(textView);
}