const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.Application";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onStartup);
  app.activate.connect(onActivate);

  return app.run(args);
}

void onActivate() {
  print("Hello there!\n");
}

void onStartup() {
  print("Initializing... Done!\n");
}