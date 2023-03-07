const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Fixed";
const string appTitle = "GtkFixed";

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
  var win = new Gtk.ApplicationWindow(self as Gtk.Application) { title = appTitle};
  var fxd = new Gtk.Fixed() { visible = true };

  fxd.put(new Gtk.Label("A") { visible = true }, 10, 20);
  fxd.put(new Gtk.Label("B") { visible = true }, 100, 200);
  fxd.put(new Gtk.Label("C") { visible = true }, 120, 326);

  win.add(fxd);
  win.set_default_size(400, 400);
}