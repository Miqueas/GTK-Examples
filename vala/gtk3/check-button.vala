const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.CheckButton";
const string APP_TITLE = "Gtk.CheckButton";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void on_app_startup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var button = new Gtk.CheckButton.with_label("OFF");

  window.add(button);
  window.title = APP_TITLE;
  window.border_width = 10;
  window.set_default_size(400, 400);

  button.active = false;
  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.visible = true;
  button.toggled.connect((self) => { self.label = self.active ? "ON" : "OFF"; });
}