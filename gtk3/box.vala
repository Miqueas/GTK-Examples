const string app_id = "io.github.Miqueas.Vala-GTK-Examples.Gtk3.Box";
static int count = 0;

int main(string[] args) {
  var app = new Gtk.Application(app_id, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(startup);
  app.activate.connect(activate);

  return app.run(args);
}

void activate(Application self) {
  var win = (self as Gtk.Application)?.get_active_window();
  win?.present();
}

void startup(Application self) {
  var win = new Gtk.ApplicationWindow(self as Gtk.Application);
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var lbl = new Gtk.Label("Click the button");
  var btn = new Gtk.Button.with_label("🤔");

  win.child = box;
  win.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;

  btn.clicked.connect(clicked);
  btn.halign = Gtk.Align.CENTER;
  btn.valign = Gtk.Align.CENTER;

  box.pack_start(lbl, false, false, 0);
  box.pack_start(btn, false, false, 0);
}

void clicked(Gtk.Button self) {
  print("You clicked %d times!\n", ++count);
}