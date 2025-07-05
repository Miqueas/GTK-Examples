const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ComboBox";
const string appTitle = "GtkComboBox";
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

  with (window) {
    add(box);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (comboBox) {
    model = listStore;
    active = 0;
    pack_start(renderer, true);
    add_attribute(renderer, "text", 0);
    changed.connect((self) => {
      var hint = @"Option $(self.active) selected ($(items[self.active]))\n";
      hintLabel.label = hint;
      print(hint);
    });
  }

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(messageLabel, false, true, 0);
    pack_start(comboBox, false, true, 0);
    pack_start(hintLabel, false, true, 0);
    show_all();
  }
}