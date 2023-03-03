const string app_id = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ApplicationWindow";

int main(string[] args) {
  var app = new Gtk.Application(app_id, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(startup);
  app.activate.connect(activate);

  return app.run(args);
}

void activate(Application self) {
  var win = (self as Gtk.Application)?.get_active_window();
  win?.present();
}

void startup(Application self) {
  var win = new Gtk.ApplicationWindow(self as Gtk.Application);
  win.set_default_size(400, 400);
}