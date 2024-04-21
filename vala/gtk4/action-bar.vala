const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.ActionBar";
const string appTitle = "GtkActionBar";

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
  var actionBar = new Gtk.ActionBar();
  var actionBarLabel = new Gtk.Label("Some information");
  var actionBarButton = new Gtk.Button.with_label("A button");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var boxLabel = new Gtk.Label("App content");
  var headerBar = new Gtk.HeaderBar();
  var titleLabel = new Gtk.Label(appTitle);

  with (window) {
    child = box;
    set_titlebar(headerBar);
    set_default_size(400, 400);
  }

  with (boxLabel) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    hexpand = true;
    vexpand = true;
  }

  with (headerBar) {
    title_widget = titleLabel;
    show_title_buttons = true;
  }

  with (actionBar) {
    pack_start(actionBarLabel);
    pack_end(actionBarButton);
  }

  with (box) {
    append(boxLabel);
    append(actionBar);
  }
}