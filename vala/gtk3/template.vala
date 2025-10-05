const string APP_ID = "io.github.Miqueas.GTK-Examples.Gtk3.Template";
const string[] greetings = { "Hello!", "¡Hola!", "Bonjour!", "Ciao!", "こんにちは！" };

int main(string[] args) {
  return new App().run(args);
}

public class App : Gtk.Application {
  public App() {
    Object(
      application_id: APP_ID,
      flags: 0,
      resource_base_path: "/io/github/Miqueas/GTK-Examples"
    );
  }

  protected override void activate() {
    active_window.present();
  }

  protected override void startup() {
    base.startup();
    new Window(this);
  }
}

[GtkTemplate (ui = "/io/github/Miqueas/GTK-Examples/template.ui")]
public class Window : Gtk.ApplicationWindow {
  [GtkChild]
  public unowned Gtk.Label label;

  public Window(App app) {
    Object(application: app);
  }

  protected override void constructed() {
    Timeout.add(1000, () => {
      this.label.label = greetings[Random.int_range(0, 5)];
      return Source.CONTINUE;
    });
  }
}