#include <gtk/gtk.h>

void onAppActivate(GApplication *self, gpointer data);
void onAppStartup(GApplication *self, gpointer data);
void onDaySelected(GtkCalendar *self, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Calendar";
const gchar *appTitle = "GtkCalendar";

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
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *box, *calendar, *dateLabel;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  calendar = gtk_calendar_new();
  dateLabel = gtk_label_new("Selected date: None");

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  gtk_box_pack_start(GTK_BOX(box), calendar, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), dateLabel, FALSE, FALSE, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_widget_show_all(box);

  g_signal_connect(
    calendar,
    "day-selected",
    G_CALLBACK(onDaySelected),
    dateLabel
  );
}

void onDaySelected(GtkCalendar *self, gpointer data) {
  guint year, month, day;
  gtk_calendar_get_date(self, &year, &month, &day);
  gtk_label_set_label(
    GTK_LABEL(data),
    g_strconcat(
      "Selected date: ",
      g_date_time_format(
        g_date_time_new_local(year, month, day, 0, 0, 0),
        "%d/%m/%Y"
      ),
      NULL
    )
  );
}