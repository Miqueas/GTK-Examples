const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Box";
const string appTitle = "GtkBox";

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

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(new Gtk.Label("A label"), false, false, 0);
    pack_start(new Gtk.Button.with_label("A button"), false, false, 0);
    show_all();
  }
}