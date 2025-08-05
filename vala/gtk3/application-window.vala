const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ApplicationWindow";
const string appTitle = "GtkApplicationWindow";

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

  with (window) {
    set_titlebar(headerBar);
    set_default_size(400, 400);
  }

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }
}