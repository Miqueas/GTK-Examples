const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Box";
const string appTitle = "GtkBox";
static int count = 0;

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onStartup);
  app.activate.connect(onActivate);

  return app.run(args);
}

void onActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application) { title = appTitle };
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var label = new Gtk.Label("Click the button");
  var button = new Gtk.Button.with_label("🤔");

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;

  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.clicked.connect(onClicked);
  
  box.append(label);
  box.append(button);

  window.child = box;
  window.set_default_size(400, 400);
}

void onClicked(Gtk.Button self) {
  print("You clicked %d times!\n", ++count);
}