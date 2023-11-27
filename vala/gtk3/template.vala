const string appID = "io.github.Miqueas.GTK-Examples.Gtk3.Template";
const string[] greetings = { "Hello!", "¡Hola!", "Bonjour!", "Ciao!" };

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

[GtkTemplate (ui = "/io/github/Miqueas/GTK-Examples/template.ui")]
class Window : Gtk.ApplicationWindow {
  [GtkChild]
  public unowned Gtk.Label label;

  public Window(App app) {
    this.application = app;
  }

  public override void constructed() {
    Timeout.add(1000, () => {
      this.label.label = greetings[Random.int_range(0, 4)];
      return Source.CONTINUE;
    });
  }
}