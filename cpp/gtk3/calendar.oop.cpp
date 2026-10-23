#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.OOP.ApplicationWindow";
static const Glib::ustring APP_TITLE = "Gtk::ApplicationWindow";

class App : public Gtk::Application {
  public:
    static Glib::RefPtr<App> create() {
      return Glib::RefPtr<App>(new App());
    }

    static void on_day_selected(Gtk::Calendar* self, Gtk::Label* label) {
      guint year, month, day;

      self->get_date(year, month, day);
      label->set_label("Selected date: " + Glib::DateTime::create_local(year, month, day, 0, 0, 0).format("%d/%m/%Y"));
    }

  protected:
    App() : Gtk::Application(APP_ID) {}

    void on_activate() override {
      Gtk::Window* window = get_active_window();
      if (window) window->show_all();
    }

    void on_startup() override {
      // Required for chain-up
      Gtk::Application::on_startup();

      auto window = new Gtk::ApplicationWindow();
      auto box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
      auto calendar = new Gtk::Calendar();
      auto label = new Gtk::Label("Selected data: None");

      window->add(*box);
      window->set_title(APP_TITLE);
      window->set_border_width(10);
      window->set_default_size(400, 400);

      box->pack_start(*calendar, false, false, 0);
      box->pack_start(*label, false, false, 0);
      box->set_halign(Gtk::ALIGN_CENTER);
      box->set_valign(Gtk::ALIGN_CENTER);

      calendar->signal_day_selected().connect(sigc::bind(sigc::ptr_fun(&on_day_selected), calendar, label));
      // Or using lambdas:
      // calendar->signal_day_selected().connect([calendar, label]() {
      //   guint year, month, day;
      //   calendar->get_date(year, month, day);

      //   auto date_time = Glib::DateTime::create_local(year, month, day, 0, 0, 0);
      //   label->set_label("Selected date: " + date_time.format("%d/%m/%Y"));
      // });

      add_window(*window);
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}