#include <gtk/gtk.h>

// `GtkLevelBar` is a bar widget that can be used as a level indicator

typedef enum {
  PS_NONE = -1,
  PS_WEAK,
  PS_GOOD,
  PS_STRONG,
  PS_EXCELLENT
} PasswordStrength;

static void on_app_activate(GApplication* self, gpointer data);
static void on_app_startup(GApplication* self, gpointer data);
void on_entry_changed(GtkEditable* self, gpointer data);
gint get_matches(const gchar* pattern, const gchar* password);
const gchar* password_strength_to_string(PasswordStrength strength);
PasswordStrength check_password_strength(const gchar* password);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.LevelBar";
const static gchar* APP_TITLE = "GtkLevelBar";
const static gchar* DIGITS_PATTERN = "[0-9]";
const static gchar* LOWERCASE_PATTERN = "[a-z]";
const static gchar* UPPERCASE_PATTERN = "[A-Z]";
const static gchar* SYMBOLS_PATTERN = "\\W";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
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
  GPtrArray* shared = g_ptr_array_new();
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget* label = gtk_label_new("Create a password");
  GtkWidget* entry = gtk_entry_new();
  GtkWidget* level_bar = gtk_level_bar_new_for_interval(0.0, 4.0);
  GtkWidget* level_bar_label = gtk_label_new("");

  g_ptr_array_add(shared, level_bar);
  g_ptr_array_add(shared, level_bar_label);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), level_bar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), level_bar_label, FALSE, FALSE, 0);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_show_all(box);

  gtk_widget_set_size_request(entry, 100, -1);
  g_signal_connect(entry, "changed", G_CALLBACK(on_entry_changed), shared);

  gtk_level_bar_set_mode(GTK_LEVEL_BAR(level_bar), GTK_LEVEL_BAR_MODE_DISCRETE);
}

void on_entry_changed(GtkEditable* self, gpointer data) {
  GPtrArray* shared = (GPtrArray*) data;
  GtkLevelBar* level_bar = GTK_LEVEL_BAR(shared->pdata[0]);
  GtkLabel* level_bar_label = GTK_LABEL(shared->pdata[1]);
  const gchar* password = gtk_entry_get_text(GTK_ENTRY(self));
  PasswordStrength strength = check_password_strength(password);
  const gchar* strengthString = password_strength_to_string(strength);

  if (strength == PS_NONE) gtk_level_bar_set_value(level_bar, 0.0);
  if (strength == PS_WEAK) gtk_level_bar_set_value(level_bar, 1.0);
  if (strength == PS_GOOD) gtk_level_bar_set_value(level_bar, 2.0);
  if (strength == PS_STRONG) gtk_level_bar_set_value(level_bar, 3.0);
  if (strength == PS_EXCELLENT) gtk_level_bar_set_value(level_bar, 4.0);

  gtk_label_set_label(
    level_bar_label,
    strengthString == NULL ? "Invalid" : strengthString
  );
}

gint get_matches(const gchar* pattern, const gchar* password) {
  GRegex* regex = g_regex_new(pattern, 0, 0, NULL);
  size_t length = strlen(password);
  gint matches = 0;

  for (gint i = 0; i < length; i++) {
    gchar slice[2] = { password[i], '\0' };
    if (g_regex_match(regex, slice, 0, NULL)) matches++;
  }

  g_regex_unref(regex);
  return matches;
}

const gchar* password_strength_to_string(PasswordStrength strength) {
  switch (strength) {
    case PS_NONE: return "No password";
    case PS_WEAK: return "Weak";
    case PS_GOOD: return "Good";
    case PS_STRONG: return "Strong";
    case PS_EXCELLENT: return "Excellent";
    default: return NULL;
  }
}

PasswordStrength check_password_strength(const gchar* password) {
  glong length = g_utf8_strlen(password, 512);
  if (length == 0) return PS_NONE;

  PasswordStrength strength = PS_WEAK;
  gint digits_matches = get_matches(DIGITS_PATTERN, password);
  gint lowercase_matches = get_matches(LOWERCASE_PATTERN, password);
  gint uppercase_matches = get_matches(UPPERCASE_PATTERN, password);
  gint symbols_matches = get_matches(SYMBOLS_PATTERN, password);

  if (digits_matches >= 8) strength++;
  if (lowercase_matches >= 12) strength++;
  if (uppercase_matches >= 6) strength++;
  if (symbols_matches >= 4) strength++;
  if (length >= 16) strength++;
  if (length >= 32) strength++;

  return strength;
}