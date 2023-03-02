const string app_id = "io.github.Miqueas.Vala-GTK-Examples.Gtk4.Fixed";

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
  var fxd = new Gtk.Fixed();

  fxd.put(new Gtk.Label("A"), 10, 20);
  fxd.put(new Gtk.Label("B"), 100, 200);
  fxd.put(new Gtk.Label("C"), 99, 326);

  win.child = fxd;
  win.set_default_size(400, 400);
}