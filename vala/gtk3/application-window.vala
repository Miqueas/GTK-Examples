const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ApplicationWindow";
const string appTitle = "GtkApplicationWindow";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onStartup);
  app.activate.connect(onActivate);

  return app.run(args);
}

void onActivate(Application self) {
  var win = (self as Gtk.Application)?.get_active_window();
  win?.present();
}

void onStartup(Application self) {
  var win = new Gtk.ApplicationWindow(self as Gtk.Application) { title = appTitle };
  win.set_default_size(400, 400);
}