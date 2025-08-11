const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ColorButton";
const string appTitle = "Gtk.ColorButton";

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
  var colorButton = new Gtk.ColorButton();

  window.add(colorButton);
  window.title = appTitle;
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