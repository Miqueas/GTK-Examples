const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ListBox";
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
  var scrolledWindow = new Gtk.ScrolledWindow(null, null);
  var button = new Gtk.Button.with_label("Load");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.add(box);
  window.title = APP_TITLE;
  window.border_width = 10;
  window.set_default_size(400, 400);

  scrolledWindow.shadow_type = Gtk.ShadowType.NONE;
  scrolledWindow.propagate_natural_width = true;
  scrolledWindow.propagate_natural_height = true;
  scrolledWindow.add(listBox);

  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.clicked.connect(self => {
    for (int i = 0; i < 100; i++) {
      var text = @"Text $(i + 1)";
      var label = new Gtk.Label(text);
      listBox.insert(label, i);
    }

    listBox.show_all();
  });

  box.pack_start(scrolledWindow, true, true, 0);
  box.pack_start(button, false, false, 0);
  box.show_all();
}