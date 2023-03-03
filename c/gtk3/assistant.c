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
  const gchar *app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.Assistant";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_DEFAULT_FLAGS);

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
  GtkWidget *win, *page1, *page2, *page3, *page4;

  win = gtk_assistant_new();
  page1 = make_page1();
  page2 = make_page2(win);
  page3 = make_page3(win);
  page4 = make_page4();

  gtk_window_set_default_size(GTK_WINDOW(win), 800, 400);

  g_signal_connect(win, "cancel", G_CALLBACK(gtk_widget_destroy), NULL);
  g_signal_connect(win, "close", G_CALLBACK(gtk_widget_destroy), NULL);

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
  GtkWidget *lbl = gtk_label_new("<span font_weight='bold' size='large'>Welcome to the GtkAssistant example</span>");
  gtk_widget_set_visible(lbl, TRUE);
  gtk_label_set_use_markup(GTK_LABEL(lbl), TRUE);

  return lbl;
}

GtkWidget* make_page2(GtkWidget *win) {
  GtkWidget *grid, *info_lbl, *name_lbl, *user_lbl, *pass_lbl;
  GtkWidget *name_entry, *user_entry, *pass_entry, *done_btn;
  GPtrArray *things;

  grid = gtk_grid_new();
  info_lbl = gtk_label_new("Fill this form");
  name_lbl = gtk_label_new("Full name");
  user_lbl = gtk_label_new("Username");
  pass_lbl = gtk_label_new("Password");
  name_entry = gtk_entry_new();
  user_entry = gtk_entry_new();
  pass_entry = gtk_entry_new();
  done_btn = gtk_button_new_with_label("Done");
  things = g_ptr_array_new_full(2, NULL);

  GtkWidget *widgets[9] = { grid, info_lbl, name_lbl, user_lbl, pass_lbl, name_entry, user_entry, pass_entry, done_btn };

  for (int i = 0; i < 9; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  g_ptr_array_insert(things, 0, win);
  g_ptr_array_insert(things, 1, grid);

  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  g_object_set(grid, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);

  for (int i = 2; i < 5; i++) {
    gtk_label_set_xalign(GTK_LABEL(widgets[i]), 0.0);
    gtk_widget_set_size_request(widgets[i], 110, -1);
  }

  gtk_widget_set_size_request(name_entry, 120, -1);
  gtk_widget_set_size_request(user_entry, 120, -1);

  gtk_entry_set_visibility(GTK_ENTRY(pass_entry), FALSE);
  gtk_entry_set_input_purpose(GTK_ENTRY(pass_entry), GTK_INPUT_PURPOSE_PASSWORD);

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
  GtkWidget *box, *info_lbl, *progress;
  GPtrArray *things;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  info_lbl = gtk_label_new("Installing the system...");
  progress = gtk_progress_bar_new();
  things = g_ptr_array_new_full(2, NULL);

  GtkWidget *widgets[3] = { box, info_lbl, progress };

  for (int i = 0; i < 3; i++)
    gtk_widget_set_visible(widgets[i], TRUE);

  g_ptr_array_insert(things, 0, win);
  g_ptr_array_insert(things, 1, box);
  g_ptr_array_insert(things, 2, progress);

  g_object_set(box, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);

  gtk_widget_set_size_request(progress, 240, -1);
  gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress), 0.2);

  g_signal_connect(GTK_ASSISTANT(win), "apply", G_CALLBACK(on_assistant_apply), things);

  gtk_box_pack_start(GTK_BOX(box), info_lbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), progress, FALSE, FALSE, 0);

  return box;
}

GtkWidget* make_page4(void) {
  GtkWidget *lbl = gtk_label_new("System installed successfully!");
  gtk_widget_set_visible(lbl, TRUE);

  return lbl;
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