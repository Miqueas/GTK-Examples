#include <gtkmm.h>
#include <iostream>

const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.OOP.ApplicationWindow";
const Glib::ustring APP_TITLE = "Gtk::ApplicationWindow";

class App : public Gtk::Application {
  public:
    static Glib::RefPtr<App> create() {
      return Glib::make_refptr_for_instance<App>(new App());
    }

  protected:
    App() : Gtk::Application(APP_ID) {}

    void on_startup() override {
      // Ensures chain-up
      Gtk::Application::on_startup();

      auto window = Gtk::make_managed<Gtk::ApplicationWindow>();
      window->set_title(APP_TITLE);
      window->set_default_size(400, 400);
      add_window(*window);
    }

    void on_activate() override {
      Gtk::Window* window = get_active_window();
      if (window != nullptr) window->present();
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}