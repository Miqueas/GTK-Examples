const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Button";
const string appTitle = "GtkButton";
static int count = 0;

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onStartup);
  app.activate.connect(onActivate);

  return app.run(args);
}

void onActivate(Application self) {
  var win = (self as Gtk.Application)?.get_active_window();
  win?.present();
}

void onStartup(Application self) {
  var win = new Gtk.ApplicationWindow(self as Gtk.Application) { title = appTitle };
  var btn = new Gtk.Button.with_label("Click me!") { visible = true };

  btn.valign = Gtk.Align.CENTER;
  btn.halign = Gtk.Align.CENTER;
  btn.clicked.connect(onClicked);

  win.add(btn);
  win.set_default_size(400, 400);
}

void onClicked(Gtk.Button self) {
  print("You clicked %d times!\n", ++count);
}