const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.HeaderBar";
const string appTitle = "GtkHeaderBar";
const string appSubtitle = "App subtitle";

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
  var header = new Gtk.HeaderBar();

  window.set_titlebar(header);
  window.set_default_size(400, 400);

  header.visible = true;
  header.title = appTitle;
  header.subtitle = appSubtitle;
  header.show_close_button = true;
}