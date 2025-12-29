#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.OOP.ApplicationWindow";
static const Glib::ustring APP_TITLE = "Gtk::ApplicationWindow";

class App : public Gtk::Application {
  public:
    static Glib::RefPtr<App> create() {
      return Glib::RefPtr<App>(new App());
    }

  protected:
    App() : Gtk::Application(APP_ID) {}

    void on_activate() override {
      Gtk::Window* window = get_active_window();
      if (window) window->present();
    }

    void on_startup() override {
      // Ensures chain-up
      Gtk::Application::on_startup();

      auto window = new Gtk::ApplicationWindow();
      window->set_title(APP_TITLE);
      window->set_default_size(400, 400);

      add_window(*window);
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}