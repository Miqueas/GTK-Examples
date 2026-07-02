#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk4.OOP.ActionBar";
static const Glib::ustring APP_TITLE = "Gtk::ActionBar";

class App : public Gtk::Application {
  public:
    static Glib::RefPtr<App> create() {
      return Glib::make_refptr_for_instance<App>(new App());
    }

  protected:
    App() : Gtk::Application(APP_ID) {}

    void on_activate() override {
      Gtk::Window* window = get_active_window();
      if (window != nullptr) window->present();
    }

    void on_startup() override {
      // Ensures chain-up
      Gtk::Application::on_startup();

      auto window = Gtk::make_managed<Gtk::ApplicationWindow>();
      auto action_bar = Gtk::make_managed<Gtk::ActionBar>();
      auto action_bar_label = Gtk::make_managed<Gtk::Label>("Something");
      auto action_bar_button = Gtk::make_managed<Gtk::Button>("A button");
      auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 0);
      auto box_label = Gtk::make_managed<Gtk::Label>("App content");

      window->set_child(*box);
      window->set_title(APP_TITLE);
      window->set_default_size(400, 400);

      action_bar->pack_start(*action_bar_label);
      action_bar->pack_end(*action_bar_button);

      box->append(*box_label);
      box->append(*action_bar);

      box_label->set_vexpand(true);
      box_label->set_hexpand(true);

      add_window(*window);
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}