const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.CheckButton";
const string appTitle = "Gtk.CheckButton";

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

  window.add(button);
  window.title = appTitle;
  window.border_width = 10;
  window.set_default_size(400, 400);

  button.active = false;
  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.visible = true;
  button.toggled.connect((self) => { self.label = self.active ? "ON" : "OFF"; });
}