const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ComboBoxText";
const string appTitle = "Gtk.ActionBar";
const string[] desktops = {
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
  var comboBox = new Gtk.ComboBoxText();
  var hintLabel = new Gtk.Label("Default id: gnome");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.add(box);
  window.title = appTitle;
  window.set_default_size(400, 400);

  foreach (var name in desktops) comboBox.append(name.down(), name);
  comboBox.set_active_id("gnome");
  comboBox.changed.connect(self => {
    hintLabel.label = @"Option id: $(self.get_active_id())";
  });

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(new Gtk.Label("Select an option"), false, true, 0);
  box.pack_start(comboBox, false, true, 0);
  box.pack_start(hintLabel, false, true, 0);
  box.show_all();
}