#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.TextView";
const static gchar* APP_TITLE = "GtkTextView";
const static gchar* LOREM_IPSUM =
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
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* text_view = gtk_text_view_new();

  gtk_container_add(GTK_CONTAINER(window), text_view);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);

  GtkTextBuffer* textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(GTK_TEXT_BUFFER(textBuffer), LOREM_IPSUM, -1);

  gtk_widget_show(text_view);
}