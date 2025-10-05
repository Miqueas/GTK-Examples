const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Application";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);

  return app.run(args);
}

void on_app_activate() {
  print("Hello there!\n");
}

void on_app_startup() {
  print("Initializing... Done!\n");
}