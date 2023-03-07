const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Box";
const string appTitle = "GtkBox";
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
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10) { visible = true };
  var lbl = new Gtk.Label("Click the button") { visible = true };
  var btn = new Gtk.Button.with_label("🤔") { visible = true };

  btn.halign = Gtk.Align.CENTER;
  btn.valign = Gtk.Align.CENTER;
  btn.clicked.connect(onClicked);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(lbl, false, false, 0);
  box.pack_start(btn, false, false, 0);

  win.add(box);
  win.set_default_size(400, 400);
}

void onClicked(Gtk.Button self) {
  print("You clicked %d times!\n", ++count);
}