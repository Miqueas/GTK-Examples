const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ColorChooserDialog";
const string APP_TITLE = "Gtk.ColorChooserDialog";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  var result = (window as Gtk.ColorChooserDialog)?.run();

  switch (result) {
    case Gtk.ResponseType.ACCEPT:
    case Gtk.ResponseType.APPLY:
    case Gtk.ResponseType.YES:
    case Gtk.ResponseType.OK: {
      var rgba = (window as Gtk.ColorChooserDialog)?.rgba;
      print("Color: %s\n", rgba?.to_string());
      break;
    }
    default: break;
  }

  window?.destroy();
}

void on_app_startup(Application self) {
  var dialog = new Gtk.ColorChooserDialog(null, null);

  dialog.title = APP_TITLE;
  dialog.application = self as Gtk.Application;
  dialog.border_width = 10;
}