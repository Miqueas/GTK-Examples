const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AspectFrame";
const string APP_TITLE = "Gtk.AspectFrame";

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
  var aspectFrame = new Gtk.AspectFrame(null, 0.5f, 0.5f, 1.7f, false);
  var button = new Gtk.Button.with_label("Long button label");

  window.add(aspectFrame);
  window.title = APP_TITLE;
  window.border_width = 10;
  window.set_default_size(400, 400);

  aspectFrame.add(button);
  aspectFrame.halign = Gtk.Align.CENTER;
  aspectFrame.valign = Gtk.Align.CENTER;
  aspectFrame.show_all();
}