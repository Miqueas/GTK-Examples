const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AspectFrame";
const string appTitle = "GtkAspectFrame";

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
  var aspectFrame = new Gtk.AspectFrame(null, 0.5f, 0.5f, 1.7f, false);
  var button = new Gtk.Button.with_label("Long button label");

  with (window) {
    add(aspectFrame);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (aspectFrame) {
    add(button);
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    show_all();
  }
}