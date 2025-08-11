const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.ActionBar";
const string appTitle = "Gtk.ActionBar";

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
  var actionBar = new Gtk.ActionBar();
  var actionBarLabel = new Gtk.Label("Some information");
  var actionBarButton = new Gtk.Button.with_label("A button");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var boxLabel = new Gtk.Label("App content");

  window.child = box;
  window.title = appTitle;
  window.set_default_size(400, 400);

  boxLabel.halign = Gtk.Align.CENTER;
  boxLabel.valign = Gtk.Align.CENTER;
  boxLabel.hexpand = true;
  boxLabel.vexpand = true;

  actionBar.pack_start(actionBarLabel);
  actionBar.pack_end(actionBarButton);

  box.append(boxLabel);
  box.append(actionBar);
}