const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AppChooserDialog";
const string appTitle = "GtkBox";

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window()
    as Gtk.AppChooserDialog;
  var result = window?.run();

  switch (result) {
    case Gtk.ResponseType.OK: {
      var info = window?.get_app_info();
      print("ID: %s\n", info?.get_id());
      print("Executable: %s\n", info?.get_executable());
      print("Description: %s\n", info?.get_description());
      print("Commandline: %s\n", info?.get_commandline());
      print("Display name: %s\n", info?.get_display_name());
      break;
    }
    default: break;
  }

  window?.destroy();
}

void onAppStartup(Application self) {
  var dialog = new Gtk.AppChooserDialog.for_content_type(null, 0, "image/png");

  with (dialog) {
    title = appTitle;
    application = self as Gtk.Application;
    border_width = 10;
  }
}