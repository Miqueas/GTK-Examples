#include <print>
#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk4.Procedural.Button";
static const Glib::ustring APP_TITLE = "Gtk::Button";

static void on_app_activate(const Glib::RefPtr<Gtk::Application>& self);
static void on_app_startup(const Glib::RefPtr<Gtk::Application>& self);

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(&on_app_activate), app));
  app->signal_startup().connect(sigc::bind(sigc::ptr_fun(&on_app_startup), app));
  return app->run(argc, argv);
}

static void on_app_activate(const Glib::RefPtr<Gtk::Application>& self) {
  Gtk::Window* window = self->get_active_window();
  if (window != nullptr) window->present();
}

static void on_app_startup(const Glib::RefPtr<Gtk::Application>& self) {
  auto window = Gtk::make_managed<Gtk::ApplicationWindow>(self);
  auto button = Gtk::make_managed<Gtk::Button>("Click Me");

  window->set_child(*button);
  window->set_title(APP_TITLE);
  window->set_default_size(400, 400);

  button->set_halign(Gtk::Align::CENTER);
  button->set_valign(Gtk::Align::CENTER);
  button->signal_clicked().connect([]() { std::println("You clicked me!"); });
}