const string app_id = "io.github.Miqueas.Vala-GTK-Examples.Gtk3.Application";

int main(string[] args) {
  var app = new Gtk.Application(app_id, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(startup);
  app.activate.connect(activate);

  return app.run(args);
}

void activate() {
  print("Hello there!\n");
}

void startup() {
  print("Initializing... Done!\n");
}