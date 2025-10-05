const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Fixed";
const string APP_TITLE = "Gtk.Fixed";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void on_app_startup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var fixed = new Gtk.Fixed();

  window.add(fixed);
  window.title = APP_TITLE;
  window.set_default_size(400, 400);

  fixed.put(new Gtk.Label("A"), 10, 20);
  fixed.put(new Gtk.Label("B"), 100, 200);
  fixed.put(new Gtk.Label("C"), 120, 326);
  fixed.show_all();
}