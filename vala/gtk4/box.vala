const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Box";
const string APP_TITLE = "Gtk.Box";
static int count = 0;

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
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var label = new Gtk.Label("Click the button");
  var button = new Gtk.Button.with_label("🤔");

  window.child = box;
  window.title = APP_TITLE;
  window.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.append(label);
  box.append(button);

  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.clicked.connect(() => print("Clicked %d times!\n", ++count));
}