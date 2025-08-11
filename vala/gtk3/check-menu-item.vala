const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.CheckMenuItem";
const string appTitle = "Gtk.CheckMenuItem";

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
  var menuBar = new Gtk.MenuBar();
  var fileMenuItem = new Gtk.MenuItem.with_label("File");
  var fileMenu = new Gtk.Menu();
  var checkMenuItem = new Gtk.CheckMenuItem.with_label("My option");

  window.add(menuBar);
  window.title = appTitle;
  window.set_default_size(400, 400);

  menuBar.add(fileMenuItem);
  menuBar.show();
  menuBar.halign = Gtk.Align.START;
  menuBar.valign = Gtk.Align.START;

  fileMenuItem.show();
  fileMenuItem.submenu = fileMenu;

  fileMenu.add(checkMenuItem);
  fileMenu.show();

  checkMenuItem.show();
  checkMenuItem.active = true;
  checkMenuItem.toggled.connect((self) => {
    print(@"Active: $(self.active ? "Yes" : "No")\n");
  });
}