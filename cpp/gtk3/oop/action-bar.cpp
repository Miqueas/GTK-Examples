#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.OOP.ActionBar";
static const Glib::ustring APP_TITLE = "Gtk::ActionBar";

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
      auto action_bar = Gtk::make_managed<Gtk::ActionBar>();
      auto action_bar_label = Gtk::make_managed<Gtk::Label>("Something");
      auto action_bar_button = Gtk::make_managed<Gtk::Button>("A button");
      auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::ORIENTATION_VERTICAL, 0);
      auto box_label = Gtk::make_managed<Gtk::Label>("App content");

      window->add(*box);
      window->set_title(APP_TITLE);
      window->set_default_size(400, 400);

      action_bar->pack_start(*action_bar_label);
      action_bar->pack_end(*action_bar_button);

      box->pack_start(*box_label, true, true, 0);
      box->pack_end(*action_bar, false, true, 0);
      box->show_all();

      add_window(*window);
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}