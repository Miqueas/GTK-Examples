const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Box";
const string appTitle = "Gtk.Box";

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
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.add(box);
  window.title = appTitle;
  window.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(new Gtk.Label("A label"), false, false, 0);
  box.pack_start(new Gtk.Button.with_label("A button"), false, false, 0);
  box.show_all();
}