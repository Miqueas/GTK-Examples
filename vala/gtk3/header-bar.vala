const string app_id = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.HeaderBar";

int main(string[] args) {
  var app = new Gtk.Application(app_id, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(startup);
  app.activate.connect(activate);

  return app.run(args);
}

void activate(Application self) {
  var win = (self as Gtk.Application)?.get_active_window();
  win?.present();
}

void startup(Application self) {
  var win = new Gtk.ApplicationWindow(self as Gtk.Application);
  var header = new Gtk.HeaderBar();

  header.title = "My app";
  header.subtitle = "An awesome app that you'll love";
  header.show_close_button = true;

  win.set_titlebar(header);
  win.set_default_size(400, 400);
}