const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Entry";
const string APP_TITLE = "Gtk.Entry";

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
  var label = new Gtk.Label("");
  var entry = new Gtk.Entry();
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.add(box);
  window.title = APP_TITLE;
  window.set_default_size(400, 400);

  entry.key_release_event.connect(() => {
    label.label = entry.text;
    return true;
  });

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(new Gtk.Label("Enter some text"), false);
  box.pack_start(entry, false);
  box.pack_start(label, false);
  box.show_all();
}