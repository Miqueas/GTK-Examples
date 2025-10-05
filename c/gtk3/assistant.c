#include <gtk/gtk.h>

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
static void on_done_button_clicked(GtkButton* self, GPtrArray* data);
static void on_assistant_apply(GtkAssistant* self, GPtrArray* data);
static gboolean progress_bar_update_function(gpointer data);
static GtkWidget* build_page_1(void);
static GtkWidget* build_page_2(GtkWidget* assistant);
static GtkWidget* build_page_3(GtkWidget* assistant);
static GtkWidget* build_page_4(void);

const static gchar* app_id = "io.github.Miqueas.GTK-Examples.C.Gtk3.Assistant";
const static gchar* app_title = "GtkAssistant";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(app_id, 0);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;
}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  GtkWidget* window = gtk_assistant_new();
  GtkWidget* page_1 = build_page_1();
  GtkWidget* page_2 = build_page_2(window);
  GtkWidget* page_3 = build_page_3(window);
  GtkWidget* page_4 = build_page_4();

  gtk_window_set_title(GTK_WINDOW(window), app_title);
  gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(self));
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
  g_signal_connect(window, "cancel", G_CALLBACK(gtk_widget_destroy), NULL);
  g_signal_connect(window, "close", G_CALLBACK(gtk_widget_destroy), NULL);

  gtk_assistant_append_page(GTK_ASSISTANT(window), page_1);
  gtk_assistant_append_page(GTK_ASSISTANT(window), page_2);
  gtk_assistant_append_page(GTK_ASSISTANT(window), page_3);
  gtk_assistant_append_page(GTK_ASSISTANT(window), page_4);

  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page_1, "Welcome");
  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page_2, "Create account");
  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page_3, "Installing system");
  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page_4, "Summary");

  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page_1, GTK_ASSISTANT_PAGE_INTRO);
  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page_2, GTK_ASSISTANT_PAGE_CONFIRM);
  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page_3, GTK_ASSISTANT_PAGE_PROGRESS);
  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page_4, GTK_ASSISTANT_PAGE_SUMMARY);

  gtk_assistant_set_page_complete(GTK_ASSISTANT(window), page_1, TRUE);

  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(window));
}

static GtkWidget* build_page_1(void) {
  const gchar* label_text = "<span font='Bold 16'>Welcome to the GtkAssistant example</span>";
  GtkWidget* label = gtk_label_new(label_text);
  gtk_widget_set_visible(label, TRUE);
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);

  return label;
}

static GtkWidget* build_page_2(GtkWidget* assistant) {
  GtkWidget* grid = gtk_grid_new();
  GtkWidget* info_label = gtk_label_new("Fill this form");
  GtkWidget* name_label = gtk_label_new("Full name");
  GtkWidget* username_label = gtk_label_new("Username");
  GtkWidget* password_label = gtk_label_new("Password");
  GtkWidget* name_entry = gtk_entry_new();
  GtkWidget* username_entry = gtk_entry_new();
  GtkWidget* password_entry = gtk_entry_new();
  GtkWidget* done_button = gtk_button_new_with_label("Done");
  GPtrArray* data = g_ptr_array_new_full(2, NULL);

  g_ptr_array_insert(data, 0, assistant);
  g_ptr_array_insert(data, 1, grid);

  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

  gtk_widget_set_size_request(name_label, 110, -1);
  gtk_widget_set_size_request(username_label, 110, -1);
  gtk_widget_set_size_request(password_label, 110, -1);

  gtk_widget_set_size_request(name_entry, 120, -1);
  gtk_widget_set_size_request(username_entry, 120, -1);
  gtk_widget_set_size_request(password_entry, 120, -1);

  gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
  gtk_entry_set_input_purpose(GTK_ENTRY(password_entry), GTK_INPUT_PURPOSE_PASSWORD);

  g_signal_connect(done_button, "clicked", G_CALLBACK(on_done_button_clicked), data);

  gtk_grid_attach(GTK_GRID(grid), info_label,   0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), name_label,   0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), username_label,   0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), password_label,   0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), done_button,   1, 4, 1, 1);
  gtk_widget_show_all(grid);

  return grid;
}

static GtkWidget* build_page_3(GtkWidget* assistant) {
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* info_label = gtk_label_new("Installing the system...");
  GtkWidget* progress_bar = gtk_progress_bar_new();
  GPtrArray* data = g_ptr_array_new_full(2, NULL);

  g_ptr_array_insert(data, 0, assistant);
  g_ptr_array_insert(data, 1, box);
  g_ptr_array_insert(data, 2, progress_bar);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  gtk_widget_set_size_request(progress_bar, 240, -1);
  gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), 0.2);

  g_signal_connect(GTK_ASSISTANT(assistant), "apply", G_CALLBACK(on_assistant_apply), data);

  gtk_box_pack_start(GTK_BOX(box), info_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), progress_bar, FALSE, FALSE, 0);
  gtk_widget_show_all(box);

  return box;
}

static GtkWidget* build_page_4(void) {
  GtkWidget* label = gtk_label_new("System installed successfully!");
  gtk_widget_set_visible(label, TRUE);

  return label;
}

static void on_done_button_clicked(GtkButton* self, GPtrArray* data) {
  GtkAssistant* assistant = GTK_ASSISTANT(g_ptr_array_index(data, 0));
  GtkWidget* page = GTK_WIDGET(g_ptr_array_index(data, 1));
  gtk_assistant_set_page_complete(assistant, page, TRUE);
}

static void on_assistant_apply(GtkAssistant* self, GPtrArray* data) {
  g_timeout_add(200, progress_bar_update_function, data);
}

static gboolean progress_bar_update_function(gpointer data) {
  GPtrArray* arr = (GPtrArray*) data;
  GtkProgressBar* progress_bar = GTK_PROGRESS_BAR(g_ptr_array_index(arr, 2));
  GtkAssistant* assistant = GTK_ASSISTANT(g_ptr_array_index(arr, 0));
  GtkWidget* page = GTK_WIDGET(g_ptr_array_index(arr, 1));
  gdouble fraction = gtk_progress_bar_get_fraction(progress_bar);

  if (fraction == 1 || fraction == 1.0) {
    gtk_assistant_set_page_complete(assistant, page, TRUE);
    gtk_assistant_commit(assistant);
    return G_SOURCE_REMOVE;
  } else if (fraction < 0) {
    gtk_progress_bar_pulse(progress_bar);
  } else {
    gtk_progress_bar_set_fraction(progress_bar, fraction + 0.1);
  }

  return G_SOURCE_CONTINUE;
}