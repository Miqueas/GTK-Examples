const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ActionBar";
const string APP_TITLE = "Gtk.ActionBar";

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
  var actionBar = new Gtk.ActionBar();
  var actionBarLabel = new Gtk.Label("Some information");
  var actionBarButton = new Gtk.Button.with_label("A button");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var boxLabel = new Gtk.Label("App content");

  window.add(box);
  window.title = APP_TITLE;
  window.set_default_size(400, 400);

  actionBar.pack_start(actionBarLabel);
  actionBar.pack_end(actionBarButton);

  box.pack_start(actionBar, false, true, 0);
  box.pack_start(boxLabel, true, true, 0);
  box.pack_end(actionBar, false, true, 0);
  box.show_all();
}