const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Fixed";
const string appTitle = "Gtk.Fixed";

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
  var fixed = new Gtk.Fixed();

  window.child = fixed;
  window.title = appTitle;
  window.set_default_size(400, 400);

  fixed.put(new Gtk.Label("A"), 10, 20);
  fixed.put(new Gtk.Label("B"), 100, 200);
  fixed.put(new Gtk.Label("C"), 99, 326);
}