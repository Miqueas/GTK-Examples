const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ActionBar";
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
  var headerBar = new Gtk.HeaderBar();
  var actionBar = new Gtk.ActionBar();
  var actionBarLabel = new Gtk.Label("Some information");
  var actionBarButton = new Gtk.Button.with_label("A button");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var boxLabel = new Gtk.Label("App content");

  with (window) {
    set_titlebar(headerBar);
    set_default_size(400, 400);
    add(box);
  }

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }

  with (actionBar) {
    pack_start(actionBarLabel);
    pack_end(actionBarButton);
  }

  with (box) {
    pack_start(boxLabel, true, true, 0);
    pack_end(actionBar, false, true, 0);
    show_all();
  }
}