const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ComboBoxText";
const string appTitle = "GtkActionBar";
const string[] comboBoxTextValues = {
  "GNOME", "Plasma",
  "Pantheon", "XFCE",
  "MATE", "Cinnamon",
  "LXDE", "LXQT",
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
  var headerBar = new Gtk.HeaderBar();
  var comboBox = new Gtk.ComboBoxText();
  var hintLabel = new Gtk.Label("Default id: gnome");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  with (window) {
    add(box);
    set_titlebar(headerBar);
    set_default_size(400, 400);
  }

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }

  with (comboBox) {
    foreach (var name in comboBoxTextValues) append(name.down(), name);
    set_active_id("gnome");
    changed.connect(self => hintLabel.label = @"Option id: $(self.get_active_id())");
  }

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(new Gtk.Label("Select an option"), false, true, 0);
    pack_start(comboBox, false, true, 0);
    pack_start(hintLabel, false, true, 0);
    show_all();
  }
}