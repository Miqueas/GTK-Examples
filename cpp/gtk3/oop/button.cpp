#include <print>
#include <gtkmm.h>
#include <iostream>

const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.OOP.Button";
const Glib::ustring APP_TITLE = "Gtk::Button";

class App : public Gtk::Application {
  public:
    static Glib::RefPtr<App> create() {
      return Glib::RefPtr<App>(new App());
    }

  protected:
    App() : Gtk::Application(APP_ID) {}

    void on_startup() override {
      // Ensures chain-up
      Gtk::Application::on_startup();

      auto window = new Gtk::ApplicationWindow();
      auto button = Gtk::make_managed<Gtk::Button>("Click Me");

      window->add(*button);
      window->set_title(APP_TITLE);
      window->set_default_size(400, 400);

      button->show();
      button->set_halign(Gtk::Align::ALIGN_CENTER);
      button->set_valign(Gtk::Align::ALIGN_CENTER);
      button->signal_clicked().connect([]() {
        std::println("You clicked me!");
      });

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