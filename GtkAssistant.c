#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);
void on_done_btn_clicked(GtkButton *self, GPtrArray *data);
void on_assistant_apply(GtkAssistant *self, GPtrArray *data);
gboolean timed_func(gpointer data);
GtkWidget* make_page1(void);
GtkWidget* make_page2(GtkWidget *win);
GtkWidget* make_page3(GtkWidget *win);
GtkWidget* make_page4(void);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkAssistant";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_ASSISTANT,
    "use-header-bar", TRUE,
    "default-width", 800,
    "default-height", 400,
    NULL
  );

  g_signal_connect(win, "cancel", G_CALLBACK(gtk_widget_destroy), NULL);
  g_signal_connect(win, "close", G_CALLBACK(gtk_widget_destroy), NULL);

  GtkWidget *page1 = make_page1();
  GtkWidget *page2 = make_page2(win);
  GtkWidget *page3 = make_page3(win);
  GtkWidget *page4 = make_page4();

  gtk_assistant_append_page(GTK_ASSISTANT(win), page1);
  gtk_assistant_append_page(GTK_ASSISTANT(win), page2);
  gtk_assistant_append_page(GTK_ASSISTANT(win), page3);
  gtk_assistant_append_page(GTK_ASSISTANT(win), page4);

  gtk_assistant_set_page_title(GTK_ASSISTANT(win), page1, "Welcome");
  gtk_assistant_set_page_title(GTK_ASSISTANT(win), page2, "Create account");
  gtk_assistant_set_page_title(GTK_ASSISTANT(win), page3, "Installing system");
  gtk_assistant_set_page_title(GTK_ASSISTANT(win), page4, "Summary");

  gtk_assistant_set_page_type(GTK_ASSISTANT(win), page1, GTK_ASSISTANT_PAGE_INTRO);
  gtk_assistant_set_page_type(GTK_ASSISTANT(win), page2, GTK_ASSISTANT_PAGE_CONFIRM);
  gtk_assistant_set_page_type(GTK_ASSISTANT(win), page3, GTK_ASSISTANT_PAGE_PROGRESS);
  gtk_assistant_set_page_type(GTK_ASSISTANT(win), page4, GTK_ASSISTANT_PAGE_SUMMARY);

  gtk_assistant_set_page_complete(GTK_ASSISTANT(win), page1, TRUE);

  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(win));
}

GtkWidget* make_page1(void) {
  return g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "<span font_weight='bold' size='large'>Welcome to the GtkAssistant example</span>",
    "use-markup", TRUE,
    NULL
  );
}

GtkWidget* make_page2(GtkWidget *win) {
  GtkWidget *grid = g_object_new(
    GTK_TYPE_GRID,
    "visible", TRUE,
    "column-spacing", 10,
    "row-spacing", 10,
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  GPtrArray *things = g_ptr_array_new_full(2, NULL);
  g_ptr_array_insert(things, 0, win);
  g_ptr_array_insert(things, 1, grid);

  GtkWidget *info_lbl = g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "Fill this form", NULL);
  GtkWidget *name_lbl = g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "width-request", 110, "xalign", 0.0, "label", "Full name", NULL);
  GtkWidget *user_lbl = g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "width-request", 110, "xalign", 0.0, "label", "Username", NULL);
  GtkWidget *pass_lbl = g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "width-request", 110, "xalign", 0.0, "label", "Password", NULL);
  GtkWidget *name_entry = g_object_new(GTK_TYPE_ENTRY, "visible", TRUE, "width-request", 120, NULL);
  GtkWidget *user_entry = g_object_new(GTK_TYPE_ENTRY, "visible", TRUE, "width-request", 120, NULL);
  GtkWidget *pass_entry = g_object_new(GTK_TYPE_ENTRY, "visible", TRUE, "input-purpose", GTK_INPUT_PURPOSE_PASSWORD, NULL);
  GtkWidget *done_btn = g_object_new(GTK_TYPE_BUTTON, "visible", TRUE, "label", "Done", NULL);

  g_signal_connect(done_btn, "clicked", G_CALLBACK(on_done_btn_clicked), things);

  gtk_grid_attach(GTK_GRID(grid), info_lbl,   0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), name_lbl,   0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), user_lbl,   0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), user_entry, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), pass_lbl,   0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), pass_entry, 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), done_btn,   1, 4, 1, 1);

  return grid;
}

GtkWidget* make_page3(GtkWidget *win) {
  GtkWidget *box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    "spacing", 10,
    "valign", GTK_ALIGN_CENTER,
    "halign", GTK_ALIGN_CENTER,
    NULL
  );

  GtkWidget *info_lbl = g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "Installing the system...", NULL);
  GtkWidget *progress = g_object_new(GTK_TYPE_PROGRESS_BAR, "visible", TRUE, "pulse-step", 0.2, "width-request", 240, NULL);

  GPtrArray *things = g_ptr_array_new_full(2, NULL);
  g_ptr_array_insert(things, 0, win);
  g_ptr_array_insert(things, 1, box);
  g_ptr_array_insert(things, 2, progress);

  g_signal_connect(GTK_ASSISTANT(win), "apply", G_CALLBACK(on_assistant_apply), things);

  gtk_box_pack_start(GTK_BOX(box), info_lbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), progress, FALSE, FALSE, 0);

  return box;
}

GtkWidget* make_page4(void) {
  return g_object_new(
    GTK_TYPE_LABEL,
    "visible", TRUE,
    "label", "System installed successfully!",
    NULL
  );
}

void on_done_btn_clicked(GtkButton *self, GPtrArray *data) {
  GtkAssistant *win = GTK_ASSISTANT(g_ptr_array_index(data, 0));
  GtkWidget *grid = GTK_WIDGET(g_ptr_array_index(data, 1));
  gtk_assistant_set_page_complete(win, grid, TRUE);
}

void on_assistant_apply(GtkAssistant *self, GPtrArray *data) {
  g_timeout_add(1000, timed_func, data);
}

gboolean timed_func(gpointer data) {
  GPtrArray *arr = (GPtrArray *) data;

  GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(g_ptr_array_index(arr, 2));
  GtkAssistant *win = GTK_ASSISTANT(g_ptr_array_index(arr, 0));
  GtkWidget *page = GTK_WIDGET(g_ptr_array_index(arr, 1));
 
  gdouble fract = gtk_progress_bar_get_fraction(progress_bar);

  if (fract == 1 || fract == 1.0) {
    gtk_assistant_set_page_complete(win, page, TRUE);
    gtk_assistant_commit(win);
    return G_SOURCE_REMOVE;
  } else if (fract < 0) {
    gtk_progress_bar_pulse(progress_bar);
    return G_SOURCE_CONTINUE;
  } else {
    gtk_progress_bar_set_fraction(progress_bar, fract + 0.1);
    return G_SOURCE_CONTINUE;
  }

  return G_SOURCE_CONTINUE;
}