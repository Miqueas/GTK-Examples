const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Label";
const string appTitle = "GtkLabel";

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
  var label = new Gtk.Label("Hi there!");

  window.title = appTitle;
  window.add(label);
  window.set_default_size(400, 400);

  label.visible = true;
}