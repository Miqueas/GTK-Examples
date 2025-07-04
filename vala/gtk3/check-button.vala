const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.CheckButton";
const string appTitle = "GtkCheckButton";

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
  var button = new Gtk.CheckButton.with_label("OFF");

  with (window) {
    add(button);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (button) {
    active = false;
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    visible = true;
    toggled.connect((self) => { self.label = self.active ? "ON" : "OFF"; });
  }
}