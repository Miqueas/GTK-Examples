const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AppChooserDialog";
const string APP_TITLE = "Gtk.AppChooserDialog";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var app = self as Gtk.Application;
  var window = app?.get_active_window() as Gtk.AppChooserDialog;
  var result = window?.run();

  switch (result) {
    case Gtk.ResponseType.OK:
      var info = window?.get_app_info();
      print("ID: %s\n", info?.get_id());
      print("Executable: %s\n", info?.get_executable());
      print("Description: %s\n", info?.get_description());
      print("Commandline: %s\n", info?.get_commandline());
      print("Display name: %s\n", info?.get_display_name());
      break;
    default: break;
  }

  window?.destroy();
}

void on_app_startup(Application self) {
  var dialog = new Gtk.AppChooserDialog.for_content_type(null, 0, "image/png");

  dialog.title = APP_TITLE;
  dialog.application = self as Gtk.Application;
  dialog.border_width = 10;
}