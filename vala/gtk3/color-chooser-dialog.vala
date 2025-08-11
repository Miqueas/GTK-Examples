const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.ColorChooserDialog";
const string appTitle = "Gtk.ColorChooserDialog";

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
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

void onAppStartup(Application self) {
  var dialog = new Gtk.ColorChooserDialog(null, null);

  dialog.title = appTitle;
  dialog.application = self as Gtk.Application;
  dialog.border_width = 10;
}