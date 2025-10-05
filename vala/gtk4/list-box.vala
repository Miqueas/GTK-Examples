const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.ListBox";
const string APP_TITLE = "Gtk.ListBox";

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
  var listBox = new Gtk.ListBox();
  var scrolledWindow = new Gtk.ScrolledWindow();
  var button = new Gtk.Button.with_label("Load");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.child = box;
  window.title = APP_TITLE;
  window.set_default_size(400, 400);

  scrolledWindow.child = listBox;
  scrolledWindow.vexpand = true;
  scrolledWindow.propagate_natural_width = true;
  scrolledWindow.propagate_natural_height = true;

  button.margin_bottom = 10;
  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.clicked.connect(self => {
    for (int i = 0; i < 100; i++)
      listBox.insert(new Gtk.Label(@"Text $(i + 1)"), i);
  });

  box.append(scrolledWindow);
  box.append(button);
}