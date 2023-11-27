const string appID = "io.github.Miqueas.GTK-Examples.Gtk3.Template";
const string[] greetings = { "Hello!", "¡Hola!", "Bonjour!", "Ciao!", "こんにちは！" };

int main(string[] args) {
  return new App().run(args);
}

class App : Gtk.Application {
  public App() {
    Object(
      application_id: appID,
      flags: ApplicationFlags.FLAGS_NONE,
      resource_base_path: "/io/github/Miqueas/GTK-Examples"
    );
  }

  public override void activate() {
    this.active_window.present();
  }

  public override void startup() {
    base.startup();
    new Window(this);
  }
}

[GtkTemplate (ui = "/io/github/Miqueas/GTK-Examples/template.ui")]
class Window : Gtk.ApplicationWindow {
  [GtkChild]
  public unowned Gtk.Label label;

  public Window(App app) {
    Object(application: app);
  }

  public override void constructed() {
    Timeout.add(1000, () => {
      this.label.label = greetings[Random.int_range(0, 5)];
      return Source.CONTINUE;
    });
  }
}