const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Entry";
const string appTitle = "GtkEntry";

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
  var headerBar = new Gtk.HeaderBar();
  var label = new Gtk.Label("");
  var entry = new Gtk.Entry();
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  with (window) {
    add(box);
    set_titlebar(headerBar);
    set_default_size(400, 400);
  }

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }

  entry.key_release_event.connect(() => { label.label = entry.text; return true; });

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(new Gtk.Label("Enter some text"), false);
    pack_start(entry, false);
    pack_start(label, false);
    show_all();
  }
}