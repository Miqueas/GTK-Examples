const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ListBox";
const string appTitle = "GtkListBox";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.DEFAULT_FLAGS);
  app.startup.connect(onStartup);
  app.activate.connect(onActivate);

  return app.run(args);
}

void onActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var listBox = new Gtk.ListBox();
  var scrolledWindow = new Gtk.ScrolledWindow(null, null);
  var button = new Gtk.Button();
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.title = appTitle;
  window.default_width = 400;
  window.default_height = 400;
  window.border_width = 10;
  window.add(box);

  listBox.visible = true;

  scrolledWindow.visible = true;
  scrolledWindow.shadow_type = Gtk.ShadowType.NONE;
  scrolledWindow.propagate_natural_width = true;
  scrolledWindow.propagate_natural_height = true;
  scrolledWindow.add(listBox);

  button.visible = true;
  button.label = "Load";
  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.clicked.connect(self => {
    for (int i = 0; i < 100; i++)
      listBox.insert(new Gtk.Label(@"Text $(i + 1)") { visible = true }, i);
  });

  box.visible = true;
  box.pack_start(scrolledWindow, true, true, 0);
  box.pack_start(button, false, false, 0);
}