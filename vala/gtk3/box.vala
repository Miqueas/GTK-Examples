const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Box";
const string APP_TITLE = "Gtk.Box";

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
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.add(box);
  window.title = APP_TITLE;
  window.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(new Gtk.Label("A label"), false, false, 0);
  box.pack_start(new Gtk.Button.with_label("A button"), false, false, 0);
  box.show_all();
}