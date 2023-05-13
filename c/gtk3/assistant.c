#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onDoneButtonClicked(GtkButton *self, GPtrArray *data);
void onAssistantApply(GtkAssistant *self, GPtrArray *data);
gboolean progressBarUpdateFunction(gpointer data);
GtkWidget* doPage1(void);
GtkWidget* doPage2(GtkWidget *assistant);
GtkWidget* doPage3(GtkWidget *assistant);
GtkWidget* doPage4(void);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Assistant";
const gchar *appTitle = "GtkAssistant";

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(appID, G_APPLICATION_DEFAULT_FLAGS);

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
  GtkWidget *window, *page1, *page2, *page3, *page4;

  window = gtk_assistant_new();
  page1 = doPage1();
  page2 = doPage2(window);
  page3 = doPage3(window);
  page4 = doPage4();

  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(self));
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
  g_signal_connect(window, "cancel", G_CALLBACK(gtk_widget_destroy), NULL);
  g_signal_connect(window, "close", G_CALLBACK(gtk_widget_destroy), NULL);

  gtk_assistant_append_page(GTK_ASSISTANT(window), page1);
  gtk_assistant_append_page(GTK_ASSISTANT(window), page2);
  gtk_assistant_append_page(GTK_ASSISTANT(window), page3);
  gtk_assistant_append_page(GTK_ASSISTANT(window), page4);

  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page1, "Welcome");
  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page2, "Create account");
  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page3, "Installing system");
  gtk_assistant_set_page_title(GTK_ASSISTANT(window), page4, "Summary");

  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page1, GTK_ASSISTANT_PAGE_INTRO);
  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page2, GTK_ASSISTANT_PAGE_CONFIRM);
  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page3, GTK_ASSISTANT_PAGE_PROGRESS);
  gtk_assistant_set_page_type(GTK_ASSISTANT(window), page4, GTK_ASSISTANT_PAGE_SUMMARY);

  gtk_assistant_set_page_complete(GTK_ASSISTANT(window), page1, TRUE);

  gtk_application_add_window(GTK_APPLICATION(self), GTK_WINDOW(window));
}

GtkWidget* doPage1(void) {
  const gchar *labelText = "<span font='Bold 16'>Welcome to the GtkAssistant example</span>";
  GtkWidget *label = gtk_label_new(labelText);
  gtk_widget_set_visible(label, TRUE);
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);

  return label;
}

GtkWidget* doPage2(GtkWidget *assistant) {
  GtkWidget *grid, *infoLabel, *nameLabel, *usernameLabel, *passwordLabel;
  GtkWidget *nameEntry, *usernameEntry, *passwordEntry, *doneButton;
  GPtrArray *data;

  grid = gtk_grid_new();
  infoLabel = gtk_label_new("Fill this form");
  nameLabel = gtk_label_new("Full name");
  usernameLabel = gtk_label_new("Username");
  passwordLabel = gtk_label_new("Password");
  nameEntry = gtk_entry_new();
  usernameEntry = gtk_entry_new();
  passwordEntry = gtk_entry_new();
  doneButton = gtk_button_new_with_label("Done");
  data = g_ptr_array_new_full(2, NULL);

  g_ptr_array_insert(data, 0, assistant);
  g_ptr_array_insert(data, 1, grid);

  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

  gtk_widget_set_size_request(nameLabel, 110, -1);
  gtk_widget_set_size_request(usernameLabel, 110, -1);
  gtk_widget_set_size_request(passwordLabel, 110, -1);

  gtk_widget_set_size_request(nameEntry, 120, -1);
  gtk_widget_set_size_request(usernameEntry, 120, -1);
  gtk_widget_set_size_request(passwordEntry, 120, -1);

  gtk_entry_set_visibility(GTK_ENTRY(passwordEntry), FALSE);
  gtk_entry_set_input_purpose(GTK_ENTRY(passwordEntry), GTK_INPUT_PURPOSE_PASSWORD);

  g_signal_connect(doneButton, "clicked", G_CALLBACK(onDoneButtonClicked), data);

  gtk_grid_attach(GTK_GRID(grid), infoLabel,   0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), nameLabel,   0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), nameEntry, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), usernameLabel,   0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), usernameEntry, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), passwordLabel,   0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), passwordEntry, 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), doneButton,   1, 4, 1, 1);
  gtk_widget_show_all(grid);

  return grid;
}

GtkWidget* doPage3(GtkWidget *assistant) {
  GtkWidget *box, *infoLabel, *progressBar;
  GPtrArray *data;

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  infoLabel = gtk_label_new("Installing the system...");
  progressBar = gtk_progress_bar_new();
  data = g_ptr_array_new_full(2, NULL);

  g_ptr_array_insert(data, 0, assistant);
  g_ptr_array_insert(data, 1, box);
  g_ptr_array_insert(data, 2, progressBar);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  gtk_widget_set_size_request(progressBar, 240, -1);
  gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progressBar), 0.2);

  g_signal_connect(GTK_ASSISTANT(assistant), "apply", G_CALLBACK(onAssistantApply), data);

  gtk_box_pack_start(GTK_BOX(box), infoLabel, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), progressBar, FALSE, FALSE, 0);
  gtk_widget_show_all(box);

  return box;
}

GtkWidget* doPage4(void) {
  GtkWidget *label = gtk_label_new("System installed successfully!");
  gtk_widget_set_visible(label, TRUE);

  return label;
}

void onDoneButtonClicked(GtkButton *self, GPtrArray *data) {
  GtkAssistant *assistant = GTK_ASSISTANT(g_ptr_array_index(data, 0));
  GtkWidget *page = GTK_WIDGET(g_ptr_array_index(data, 1));
  gtk_assistant_set_page_complete(assistant, page, TRUE);
}

void onAssistantApply(GtkAssistant *self, GPtrArray *data) {
  g_timeout_add(1000, progressBarUpdateFunction, data);
}

gboolean progressBarUpdateFunction(gpointer data) {
  GPtrArray *arr = (GPtrArray *) data;

  GtkProgressBar *progressBar = GTK_PROGRESS_BAR(g_ptr_array_index(arr, 2));
  GtkAssistant *assistant = GTK_ASSISTANT(g_ptr_array_index(arr, 0));
  GtkWidget *page = GTK_WIDGET(g_ptr_array_index(arr, 1));
 
  gdouble fraction = gtk_progress_bar_get_fraction(progressBar);

  if (fraction == 1 || fraction == 1.0) {
    gtk_assistant_set_page_complete(assistant, page, TRUE);
    gtk_assistant_commit(assistant);
    return G_SOURCE_REMOVE;
  } else if (fraction < 0) {
    gtk_progress_bar_pulse(progressBar);
  } else {
    gtk_progress_bar_set_fraction(progressBar, fraction + 0.1);
  }

  return G_SOURCE_CONTINUE;
}