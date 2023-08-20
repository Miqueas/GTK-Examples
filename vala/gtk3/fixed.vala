const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Fixed";
const string appTitle = "GtkFixed";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
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

  window.title = appTitle;
  window.add(fixed);
  window.set_default_size(400, 400);

  fixed.visible = true;
  fixed.put(new Gtk.Label("A") { visible = true }, 10, 20);
  fixed.put(new Gtk.Label("B") { visible = true }, 100, 200);
  fixed.put(new Gtk.Label("C") { visible = true }, 120, 326);
}