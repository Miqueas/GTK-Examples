const string appID = "io.github.Miqueas.GTK-Examples.Gtk3.Template";

int main(string[] args) {
  return new App().run(args);
}

class App : Gtk.Application {
  public App() {
    this.application_id = appID;
    this.flags = ApplicationFlags.FLAGS_NONE;
  }

  public override void activate() {
    this.active_window.present();
  }

  public override void startup() {
    base.startup();
    new Window(this);
  }
}

class Header : Gtk.HeaderBar {
  public override void constructed() {
  }
}

class Window : Gtk.ApplicationWindow {
  public Window(App app) {
    this.application = app;
  }

  public override void constructed() {
  }
}