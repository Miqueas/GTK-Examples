const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Calendar";
const string appTitle = "Gtk.Calendar";

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onAppStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var calendar = new Gtk.Calendar();
  var dateLabel = new Gtk.Label("Selected date: None");

  window.add(box);
  window.title = appTitle;
  window.border_width = 10;
  window.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(calendar, false, false, 0);
  box.pack_start(dateLabel, false, false, 0);
  box.show_all();

  calendar.day_selected.connect((self) => {
    var date = new DateTime.local(self.year, self.month, self.day, 0, 0, 0);
    dateLabel.label = @"Selected date: $(date.format("%d/%m/%Y"))";
  });
}