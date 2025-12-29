#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.Procedural.AppChooserButton";
static const Glib::ustring APP_TITLE = "Gtk::AppChooserButton";

static void on_app_activate(Glib::RefPtr<Gtk::Application> self);
static void on_app_startup(Glib::RefPtr<Gtk::Application> self);

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(&on_app_activate), app));
  app->signal_startup().connect(sigc::bind(sigc::ptr_fun(&on_app_startup), app));
  return app->run(argc, argv);
}

static void on_app_activate(Glib::RefPtr<Gtk::Application> self) {
  Gtk::Window* window = self->get_active_window();
  if (window) window->present();
}

static void on_app_startup(Glib::RefPtr<Gtk::Application> self) {
  // Because `Gtk::ApplicationWindow` doesn't have a parent widget per se, there's
  // no point in using `Gtk::make_managed()` with it.
  auto window = new Gtk::ApplicationWindow(self);
  auto app_chooser_button = Gtk::make_managed<Gtk::AppChooserButton>("image/png");

  window->add(*app_chooser_button);
  window->set_title(APP_TITLE);
  window->set_border_width(10);
  window->set_default_size(400, 400);

  app_chooser_button->show();
  app_chooser_button->set_halign(Gtk::Align::ALIGN_CENTER);
  app_chooser_button->set_valign(Gtk::Align::ALIGN_CENTER);
}