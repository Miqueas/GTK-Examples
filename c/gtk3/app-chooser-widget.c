#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onShowAllToggled(GtkToggleButton *self, gpointer data);
void onDefaultToggled(GtkToggleButton *self, gpointer data);
void onFallbackToggled(GtkToggleButton *self, gpointer data);
void onOtherToggled(GtkToggleButton *self, gpointer data);
void onRecommendedToggled(GtkToggleButton *self, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.AppChooserWidget";
const gchar *APP_TITLE = "GtkAppChooserWidget";

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
  GPtrArray *sharedWidgets;
  GtkWidget
    *window,
    *box,
    *appChooserWidget,
    *settingsLabel,
    *showAllToggle,
    *showDefaultToggle,
    *showFallbackToggle,
    *showOtherToggle,
    *showRecommendedToggle;
  
  sharedWidgets = g_ptr_array_new();
  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  appChooserWidget = gtk_app_chooser_widget_new("image/png");
  settingsLabel = gtk_label_new("Settings:");
  showAllToggle = gtk_check_button_new_with_label("Show all applications");
  showDefaultToggle = gtk_check_button_new_with_label("Show default");
  showFallbackToggle = gtk_check_button_new_with_label("Show fallback");
  showOtherToggle = gtk_check_button_new_with_label("Show other");
  showRecommendedToggle = gtk_check_button_new_with_label("Show recommended");

  g_ptr_array_add(sharedWidgets, appChooserWidget);
  g_ptr_array_add(sharedWidgets, showAllToggle);
  g_ptr_array_add(sharedWidgets, showDefaultToggle);
  g_ptr_array_add(sharedWidgets, showFallbackToggle);
  g_ptr_array_add(sharedWidgets, showOtherToggle);
  g_ptr_array_add(sharedWidgets, showRecommendedToggle);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), appChooserWidget, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), settingsLabel, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), showAllToggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), showDefaultToggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), showFallbackToggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), showOtherToggle, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), showRecommendedToggle, FALSE, FALSE, 0);
  gtk_widget_show_all(box);

  gtk_widget_set_halign(settingsLabel, GTK_ALIGN_START);

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(showAllToggle),
    gtk_app_chooser_widget_get_show_all(
      GTK_APP_CHOOSER_WIDGET(appChooserWidget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(showDefaultToggle),
    gtk_app_chooser_widget_get_show_default(
      GTK_APP_CHOOSER_WIDGET(appChooserWidget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(showFallbackToggle),
    gtk_app_chooser_widget_get_show_fallback(
      GTK_APP_CHOOSER_WIDGET(appChooserWidget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(showOtherToggle),
    gtk_app_chooser_widget_get_show_other(
      GTK_APP_CHOOSER_WIDGET(appChooserWidget)
    )
  );

  gtk_toggle_button_set_active(
    GTK_TOGGLE_BUTTON(showRecommendedToggle),
    gtk_app_chooser_widget_get_show_recommended(
      GTK_APP_CHOOSER_WIDGET(appChooserWidget)
    )
  );

  g_signal_connect(
    showAllToggle,
    "toggled",
    G_CALLBACK(onShowAllToggled),
    sharedWidgets
  );

  g_signal_connect(
    showDefaultToggle,
    "toggled",
    G_CALLBACK(onDefaultToggled),
    sharedWidgets
  );

  g_signal_connect(
    showFallbackToggle,
    "toggled",
    G_CALLBACK(onFallbackToggled),
    sharedWidgets
  );

  g_signal_connect(
    showOtherToggle,
    "toggled",
    G_CALLBACK(onOtherToggled),
    sharedWidgets
  );

  g_signal_connect(
    showRecommendedToggle,
    "toggled",
    G_CALLBACK(onRecommendedToggled),
    sharedWidgets
  );
}

void onShowAllToggled(GtkToggleButton *self, gpointer data) {
  GPtrArray *sharedWidgets;
  GtkAppChooserWidget *appChooserWidget;
  GtkToggleButton
    *showDefaultToggle,
    *showFallbackToggle,
    *showOtherToggle,
    *showRecommendedToggle;
  gboolean showAll;

  sharedWidgets = (GPtrArray *) data;
  appChooserWidget = GTK_APP_CHOOSER_WIDGET(sharedWidgets->pdata[0]);
  showDefaultToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[2]);
  showFallbackToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[3]);
  showOtherToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[4]);
  showRecommendedToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[5]);
  showAll = gtk_toggle_button_get_active(self);

  gtk_app_chooser_widget_set_show_all(appChooserWidget, showAll);

  if (showAll) {
    gtk_toggle_button_set_active(showDefaultToggle, FALSE);
    gtk_toggle_button_set_active(showFallbackToggle, FALSE);
    gtk_toggle_button_set_active(showOtherToggle, FALSE);
    gtk_toggle_button_set_active(showRecommendedToggle, FALSE);
  }
}

void onDefaultToggled(GtkToggleButton *self, gpointer data) {
  GPtrArray *sharedWidgets;
  GtkAppChooserWidget *appChooserWidget;
  GtkToggleButton *showAllToggle;
  gboolean showAll, showDefault;

  sharedWidgets = (GPtrArray *) data;
  appChooserWidget = GTK_APP_CHOOSER_WIDGET(sharedWidgets->pdata[0]);
  showAllToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[1]);
  showAll = gtk_toggle_button_get_active(showAllToggle);
  showDefault = gtk_toggle_button_get_active(self);

  gtk_app_chooser_widget_set_show_default(appChooserWidget, showDefault);

  if (showAll && showDefault) {
    gtk_toggle_button_set_active(showAllToggle, FALSE);
  }
}

void onFallbackToggled(GtkToggleButton *self, gpointer data) {
  GPtrArray *sharedWidgets;
  GtkAppChooserWidget *appChooserWidget;
  GtkToggleButton *showAllToggle;
  gboolean showAll, showFallback;

  sharedWidgets = (GPtrArray *) data;
  appChooserWidget = GTK_APP_CHOOSER_WIDGET(sharedWidgets->pdata[0]);
  showAllToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[1]);
  showAll = gtk_toggle_button_get_active(showAllToggle);
  showFallback = gtk_toggle_button_get_active(self);

  gtk_app_chooser_widget_set_show_fallback(appChooserWidget, showFallback);

  if (showAll && showFallback) {
    gtk_toggle_button_set_active(showAllToggle, FALSE);
  }
}

void onOtherToggled(GtkToggleButton *self, gpointer data) {
  GPtrArray *sharedWidgets;
  GtkAppChooserWidget *appChooserWidget;
  GtkToggleButton *showAllToggle;
  gboolean showAll, showOther;

  sharedWidgets = (GPtrArray *) data;
  appChooserWidget = GTK_APP_CHOOSER_WIDGET(sharedWidgets->pdata[0]);
  showAllToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[1]);
  showAll = gtk_toggle_button_get_active(showAllToggle);
  showOther = gtk_toggle_button_get_active(self);

  gtk_app_chooser_widget_set_show_other(appChooserWidget, showOther);

  if (showAll && showOther) {
    gtk_toggle_button_set_active(showAllToggle, FALSE);
  }
}

void onRecommendedToggled(GtkToggleButton *self, gpointer data) {
  GPtrArray *sharedWidgets;
  GtkAppChooserWidget *appChooserWidget;
  GtkToggleButton *showAllToggle;
  gboolean showAll, showRecommended;

  sharedWidgets = (GPtrArray *) data;
  appChooserWidget = GTK_APP_CHOOSER_WIDGET(sharedWidgets->pdata[0]);
  showAllToggle = GTK_TOGGLE_BUTTON(sharedWidgets->pdata[1]);
  showAll = gtk_toggle_button_get_active(showAllToggle);
  showRecommended = gtk_toggle_button_get_active(self);

  gtk_app_chooser_widget_set_show_recommended(appChooserWidget, showRecommended);

  if (showAll && showRecommended) {
    gtk_toggle_button_set_active(showAllToggle, FALSE);
  }
}