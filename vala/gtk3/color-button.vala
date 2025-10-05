const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ColorButton";
const string APP_TITLE = "Gtk.ColorButton";

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
  var colorButton = new Gtk.ColorButton();

  window.add(colorButton);
  window.title = APP_TITLE;
  window.border_width = 10;
  window.set_default_size(400, 400);

  colorButton.show();
  colorButton.title = "Pick a Color";
  colorButton.halign = Gtk.Align.CENTER;
  colorButton.valign = Gtk.Align.CENTER;
  colorButton.color_set.connect(self => {
    print("Color: %s\n", self.rgba.to_string());
  });
}