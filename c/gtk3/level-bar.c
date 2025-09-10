#include <gtk/gtk.h>

// `GtkLevelBar` is a bar widget that can be used as a level indicator

typedef enum {
  PS_NONE = -1,
  PS_WEAK,
  PS_GOOD,
  PS_STRONG,
  PS_EXCELLENT
} PasswordStrength;

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onEntryChanged(GtkEditable *self, gpointer data);
gint getMatches(const gchar *pattern, const gchar *password);
const gchar* passwordStrengthToString(PasswordStrength strength);
PasswordStrength checkPasswordStrength(const gchar *password);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.LevelBar";
const gchar *APP_TITLE = "GtkLevelBar";
const gchar *digitsPattern = "[0-9]";
const gchar *lowercasePattern = "[a-z]";
const gchar *uppercasePattern = "[A-Z]";
const gchar *symbolsPattern = "\\W";

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
}

void onAppStartup(GApplication *self, gpointer data) {
  GPtrArray *shared = g_ptr_array_new();
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *label = gtk_label_new("Create a password");
  GtkWidget *entry = gtk_entry_new();
  GtkWidget *levelBar = gtk_level_bar_new_for_interval(0.0, 4.0);
  GtkWidget *levelBarLabel = gtk_label_new("");

  g_ptr_array_add(shared, levelBar);
  g_ptr_array_add(shared, levelBarLabel);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), levelBar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), levelBarLabel, FALSE, FALSE, 0);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_show_all(box);

  gtk_widget_set_size_request(entry, 100, -1);
  g_signal_connect(entry, "changed", G_CALLBACK(onEntryChanged), shared);

  gtk_level_bar_set_mode(GTK_LEVEL_BAR(levelBar), GTK_LEVEL_BAR_MODE_DISCRETE);
}

void onEntryChanged(GtkEditable *self, gpointer data) {
  GPtrArray *shared = (GPtrArray *) data;
  GtkLevelBar *levelBar = GTK_LEVEL_BAR(shared->pdata[0]);
  GtkLabel *levelBarLabel = GTK_LABEL(shared->pdata[1]);
  const gchar *password = gtk_entry_get_text(GTK_ENTRY(self));
  PasswordStrength strength = checkPasswordStrength(password);
  const gchar *strengthString = passwordStrengthToString(strength);

  if (strength == PS_NONE) gtk_level_bar_set_value(levelBar, 0.0);
  if (strength == PS_WEAK) gtk_level_bar_set_value(levelBar, 1.0);
  if (strength == PS_GOOD) gtk_level_bar_set_value(levelBar, 2.0);
  if (strength == PS_STRONG) gtk_level_bar_set_value(levelBar, 3.0);
  if (strength == PS_EXCELLENT) gtk_level_bar_set_value(levelBar, 4.0);

  gtk_label_set_label(
    levelBarLabel,
    strengthString == NULL ? "Invalid" : strengthString
  );
}

gint getMatches(const gchar *pattern, const gchar *password) {
  GRegex *regex = g_regex_new(pattern, 0, 0, NULL);
  size_t length = strlen(password);
  gint matches = 0;

  for (gint i = 0; i < length; i++) {
    gchar slice[2] = { password[i], '\0' };
    if (g_regex_match(regex, slice, 0, NULL)) matches++;
  }

  g_regex_unref(regex);
  return matches;
}

const gchar* passwordStrengthToString(PasswordStrength strength) {
  switch (strength) {
    case PS_NONE: return "No password";
    case PS_WEAK: return "Weak";
    case PS_GOOD: return "Good";
    case PS_STRONG: return "Strong";
    case PS_EXCELLENT: return "Excellent";
    default: return NULL;
  }
}

PasswordStrength checkPasswordStrength(const gchar *password) {
  size_t length = strlen(password);
  if (length == 0) return PS_NONE;

  PasswordStrength strength = PS_WEAK;
  gint digitsMatches = getMatches(digitsPattern, password);
  gint lowercaseMatches = getMatches(lowercasePattern, password);
  gint uppercaseMatches = getMatches(uppercasePattern, password);
  gint symbolsMatches = getMatches(symbolsPattern, password);

  if (digitsMatches >= 8) strength++;
  if (lowercaseMatches >= 12) strength++;
  if (uppercaseMatches >= 6) strength++;
  if (symbolsMatches >= 4) strength++;
  if (length >= 16) strength++;
  if (length >= 32) strength++;

  return strength;
}