#include <print>
#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.Procedural.Application";
static const Glib::ustring APP_TITLE = "Gtk::ApplicationWindow";

static void on_app_startup(Glib::RefPtr<Gtk::Application> self);
static void on_app_activate(Glib::RefPtr<Gtk::Application> self);

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(&on_app_activate), app));
  app->signal_startup().connect(sigc::bind(sigc::ptr_fun(&on_app_startup), app));
  return app->run(argc, argv);
}

static void on_app_activate(Glib::RefPtr<Gtk::Application> self) {
  std::println("::activate");
}

static void on_app_startup(Glib::RefPtr<Gtk::Application> self) {
  std::println("::startup");
}