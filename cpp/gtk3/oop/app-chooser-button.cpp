#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.OOP.AppChooserButton";
static const Glib::ustring APP_TITLE = "Gtk::AppChooserButton";

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
      auto app_chooser_button = Gtk::make_managed<Gtk::AppChooserButton>("image/png");

      window->add(*app_chooser_button);
      window->set_title(APP_TITLE);
      window->set_border_width(10);
      window->set_default_size(400, 400);

      app_chooser_button->show();
      app_chooser_button->set_halign(Gtk::Align::ALIGN_CENTER);
      app_chooser_button->set_valign(Gtk::Align::ALIGN_CENTER);

      add_window(*window);
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}