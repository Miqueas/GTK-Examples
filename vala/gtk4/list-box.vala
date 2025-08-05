const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.ListBox";
const string appTitle = "GtkListBox";

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
  var listBox = new Gtk.ListBox();
  var scrolledWindow = new Gtk.ScrolledWindow();
  var button = new Gtk.Button.with_label("Load");
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);

  window.child = box;
  window.title = appTitle;
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