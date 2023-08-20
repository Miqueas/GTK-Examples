const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Application";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);

  return app.run(args);
}

void onAppActivate() {
  print("Hello there!\n");
}

void onAppStartup() {
  print("Initializing... Done!\n");
}