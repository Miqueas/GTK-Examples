const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ColorButton";
const string appTitle = "GtkColorButton";

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

  with (window) {
    add(colorButton);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (colorButton) {
    show();
    title = "Pick a Color";
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    color_set.connect((self) => {
      print("Color: %s\n", self.rgba.to_string());
    });
  }
}