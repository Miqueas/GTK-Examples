#include <gtkmm.h>

enum class Setting {
  SHOW_ALL,
  SHOW_DEFAULT,
  SHOW_FALLBACK,
  SHOW_OTHER,
  SHOW_RECOMMENDED
};

static void on_app_startup(const Glib::RefPtr<Gtk::Application>& self);
static void on_app_activate(const Glib::RefPtr<Gtk::Application>& self);
static void on_button_toggled(Gtk::ToggleButton* self, Setting setting, std::vector<Gtk::Widget*> widgets);

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.Procedural.AppChooserWidget";
static const Glib::ustring APP_TITLE = "Gtk::AppChooserWidget";

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(&on_app_activate), app));
  app->signal_startup().connect(sigc::bind(sigc::ptr_fun(&on_app_startup), app));
  return app->run(argc, argv);
}

static void on_app_activate(const Glib::RefPtr<Gtk::Application>& self) {
  Gtk::Window* window = self->get_active_window();
  if (window) window->present();
}

static void on_app_startup(const Glib::RefPtr<Gtk::Application>& self) {
  // Because `Gtk::ApplicationWindow` doesn't have a parent widget per se, there's
  // no point in using `Gtk::make_managed()` with it.
  auto window = new Gtk::ApplicationWindow(self);
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 10);
  auto app_chooser_widget = Gtk::make_managed<Gtk::AppChooserWidget>("image/png");
  auto settings_label = Gtk::make_managed<Gtk::Label>("Settings:");
  auto show_all_toggle = Gtk::make_managed<Gtk::CheckButton>("Show all applications");
  auto show_default_toggle = Gtk::make_managed<Gtk::CheckButton>("Show default");
  auto show_fallback_toggle = Gtk::make_managed<Gtk::CheckButton>("Show fallback");
  auto show_other_toggle = Gtk::make_managed<Gtk::CheckButton>("Show other");
  auto show_recommended_toggle = Gtk::make_managed<Gtk::CheckButton>("Show recommended");

  std::vector<Gtk::Widget*> widgets{
    app_chooser_widget,
    show_all_toggle,
    show_default_toggle,
    show_fallback_toggle,
    show_other_toggle,
    show_recommended_toggle
  };

  window->add(*box);
  window->set_title(APP_TITLE);
  window->set_border_width(10);
  window->set_default_size(400, 400);

  box->pack_start(*app_chooser_widget, true, true, 0);
  box->pack_start(*settings_label, false, false, 0);
  box->pack_start(*show_all_toggle, false, false, 0);
  box->pack_start(*show_default_toggle, false, false, 0);
  box->pack_start(*show_fallback_toggle, false, false, 0);
  box->pack_start(*show_other_toggle, false, false, 0);
  box->pack_start(*show_recommended_toggle, false, false, 0);
  box->show_all();

  settings_label->set_halign(Gtk::ALIGN_START);

  show_all_toggle->set_active(app_chooser_widget->get_show_all());
  show_default_toggle->set_active(app_chooser_widget->get_show_default());
  show_fallback_toggle->set_active(app_chooser_widget->get_show_fallback());
  show_other_toggle->set_active(app_chooser_widget->get_show_other());
  show_recommended_toggle->set_active(app_chooser_widget->get_show_recommended());

  show_all_toggle->signal_toggled().connect(
    sigc::bind(
      sigc::ptr_fun(&on_button_toggled),
      show_all_toggle, Setting::SHOW_ALL,
      widgets
    )
  );

  show_default_toggle->signal_toggled().connect(
    sigc::bind(
      sigc::ptr_fun(&on_button_toggled),
      show_default_toggle,
      Setting::SHOW_DEFAULT,
      widgets
    )
  );

  show_fallback_toggle->signal_toggled().connect(
    sigc::bind(
      sigc::ptr_fun(&on_button_toggled),
      show_fallback_toggle,
      Setting::SHOW_FALLBACK,
      widgets
    )
  );

  show_other_toggle->signal_toggled().connect(
    sigc::bind(
      sigc::ptr_fun(&on_button_toggled),
      show_other_toggle,
      Setting::SHOW_OTHER,
      widgets
    )
  );

  show_recommended_toggle->signal_toggled().connect(
    sigc::bind(
      sigc::ptr_fun(&on_button_toggled),
      show_recommended_toggle,
      Setting::SHOW_RECOMMENDED,
      widgets
    )
  );
}

static void on_button_toggled(Gtk::ToggleButton* self, Setting setting, std::vector<Gtk::Widget*> widgets) {
  auto app_chooser_widget = dynamic_cast<Gtk::AppChooserWidget*>(widgets[0]);
  auto show_all_toggle = dynamic_cast<Gtk::ToggleButton*>(widgets[1]);
  bool show_all = show_all_toggle->get_active();
  bool is_active = self->get_active();

  switch (setting) {
    case Setting::SHOW_ALL:
      app_chooser_widget->set_show_all(is_active);
      if (is_active) {
        for (size_t i = 2; i < widgets.size(); i++) {
          auto toggle = dynamic_cast<Gtk::ToggleButton*>(widgets[i]);
          toggle->set_active(false);
        }
      }
      break;
    case Setting::SHOW_DEFAULT:
      app_chooser_widget->set_show_default(is_active);
      if (show_all && is_active) show_all_toggle->set_active(false);
      break;
    case Setting::SHOW_FALLBACK:
      app_chooser_widget->set_show_fallback(is_active);
      if (show_all && is_active) show_all_toggle->set_active(false);
      break;
    case Setting::SHOW_OTHER:
      app_chooser_widget->set_show_other(is_active);
      if (show_all && is_active) show_all_toggle->set_active(false);
      break;
    case Setting::SHOW_RECOMMENDED:
      app_chooser_widget->set_show_recommended(is_active);
      if (show_all && is_active) show_all_toggle->set_active(false);
      break;
    default: break;
  }
}