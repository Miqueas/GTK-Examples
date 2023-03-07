const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Fixed";
const string appTitle = "GtkFixed";

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
  var window = new Gtk.ApplicationWindow(self as Gtk.Application) { title = appTitle };
  var fixed = new Gtk.Fixed();

  fixed.put(new Gtk.Label("A"), 10, 20);
  fixed.put(new Gtk.Label("B"), 100, 200);
  fixed.put(new Gtk.Label("C"), 99, 326);

  window.child = fixed;
  window.set_default_size(400, 400);
}