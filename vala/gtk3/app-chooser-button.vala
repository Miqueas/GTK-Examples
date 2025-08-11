const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AppChooserButton";
const string appTitle = "Gtk.AppChooserButton";

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
  var appChooserButton = new Gtk.AppChooserButton("image/png");

  window.title = appTitle;
  window.border_width = 10;
  window.add(appChooserButton);
  window.set_default_size(400, 400);

  appChooserButton.visible = true;
  appChooserButton.halign = Gtk.Align.CENTER;
  appChooserButton.valign = Gtk.Align.CENTER;
}