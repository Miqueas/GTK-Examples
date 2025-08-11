const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.HeaderBar";
const string appTitle = "Gtk.HeaderBar";
const string appSubtitle = "App subtitle";

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
  var headerBar = new Gtk.HeaderBar();

  window.set_titlebar(headerBar);
  window.set_default_size(400, 400);

  headerBar.visible = true;
  headerBar.title = appTitle;
  headerBar.subtitle = appSubtitle;
  headerBar.show_close_button = true;
}