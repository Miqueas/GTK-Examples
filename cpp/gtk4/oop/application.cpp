#include <print>
#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.OOP.Application";

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
      std::println("::startup");
    }

    void on_activate() override {
      std::println("::activate");
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}