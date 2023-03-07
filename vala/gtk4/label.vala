const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Label";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onStartup);
  app.activate.connect(onActivate);

  return app.run(args);
}

void onActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var label = new Gtk.Label("Hi there!");

  window.child = label;
  window.set_default_size(400, 400);
}