const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.CheckMenuItem";
const string APP_TITLE = "Gtk.CheckMenuItem";

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
  var menuBar = new Gtk.MenuBar();
  var fileMenuItem = new Gtk.MenuItem.with_label("File");
  var fileMenu = new Gtk.Menu();
  var checkMenuItem = new Gtk.CheckMenuItem.with_label("My option");

  window.add(menuBar);
  window.title = APP_TITLE;
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