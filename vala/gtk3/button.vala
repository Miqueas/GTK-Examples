const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Button";
const string appTitle = "Gtk.Button";
static int count = 0;

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
  var button = new Gtk.Button.with_label("Click me!");

  window.add(button);
  window.title = appTitle;
  window.set_default_size(400, 400);

  button.visible = true;
  button.valign = Gtk.Align.CENTER;
  button.halign = Gtk.Align.CENTER;
  button.clicked.connect(self => print("Clicked %d times!\n", ++count));
}