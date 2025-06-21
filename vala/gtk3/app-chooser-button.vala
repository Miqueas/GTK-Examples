const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AppChooserButton";
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
  var appChooserButton = new Gtk.AppChooserButton("image/png");

  with (window) {
    title = appTitle;
    border_width = 10;
    add(appChooserButton);
    set_default_size(400, 400);
  }

  with (appChooserButton) {
    visible = true;
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
  }
}