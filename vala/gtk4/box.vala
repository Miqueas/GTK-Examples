const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Box";
const string appTitle = "GtkBox";
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
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var label = new Gtk.Label("Click the button");
  var button = new Gtk.Button.with_label("🤔");

  window.child = box;
  window.title = appTitle;
  window.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.append(label);
  box.append(button);

  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.clicked.connect(onButtonClicked);
}

void onButtonClicked(Gtk.Button self) {
  print("You clicked %d times!\n", ++count);
}