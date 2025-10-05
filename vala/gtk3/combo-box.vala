const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ComboBox";
const string APP_TITLE = "Gtk.ComboBox";
const string[] items = {
  "GNOME",
  "KDE Plasma",
  "XFCE",
  "MATE",
  "Cinnamon",
  "Pantheon",
  "LXDE",
  "LXQT"
};

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
  var messageLabel = new Gtk.Label("Select an option");
  var comboBox = new Gtk.ComboBox();
  var hintLabel = new Gtk.Label("Default option: 0");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var renderer = new Gtk.CellRendererText();
  var listStore = new Gtk.ListStore(1, typeof(string));
  Gtk.TreeIter iter;

  foreach (var item in items) {
    listStore.append(out iter);
    listStore.set(iter, 0, item);
  }

  window.add(box);
  window.title = APP_TITLE;
  window.border_width = 10;
  window.set_default_size(400, 400);

  comboBox.model = listStore;
  comboBox.active = 0;
  comboBox.pack_start(renderer, true);
  comboBox.add_attribute(renderer, "text", 0);
  comboBox.changed.connect((self) => {
    var hint = @"Option $(self.active) selected ($(items[self.active]))\n";
    hintLabel.label = hint;
    print(hint);
  });

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(messageLabel, false, true, 0);
  box.pack_start(comboBox, false, true, 0);
  box.pack_start(hintLabel, false, true, 0);
  box.show_all();
}