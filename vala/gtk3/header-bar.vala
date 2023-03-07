const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.HeaderBar";
const string appTitle = "GtkHeaderBar";
const string appSubtitle = "A (client-side) window decoration widget";

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
  var header = new Gtk.HeaderBar() { visible = true };

  header.title = appTitle;
  header.subtitle = appSubtitle;
  header.show_close_button = true;

  window.set_titlebar(header);
  window.set_default_size(400, 400);
}