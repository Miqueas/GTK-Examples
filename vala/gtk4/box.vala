const string app_id = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Box";
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

  box.append(lbl);
  box.append(btn);
}

void clicked(Gtk.Button self) {
  print("You clicked %d times!\n", ++count);
}