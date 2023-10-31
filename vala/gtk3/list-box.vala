const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ListBox";
const string appTitle = "GtkListBox";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
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
  var listBox = new Gtk.ListBox();
  var scrolledWindow = new Gtk.ScrolledWindow(null, null);
  var button = new Gtk.Button.with_label("Load");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.title = appTitle;
  window.border_width = 10;
  window.add(box);
  window.set_default_size(400, 400);

  scrolledWindow.shadow_type = Gtk.ShadowType.NONE;
  scrolledWindow.propagate_natural_width = true;
  scrolledWindow.propagate_natural_height = true;
  scrolledWindow.add(listBox);

  button.halign = Gtk.Align.CENTER;
  button.valign = Gtk.Align.CENTER;
  button.clicked.connect(self => {
    for (int i = 0; i < 100; i++)
      listBox.insert(new Gtk.Label(@"Text $(i + 1)") { visible = true }, i);
  });

  box.pack_start(scrolledWindow, true, true, 0);
  box.pack_start(button, false, false, 0);
  box.show_all();
}