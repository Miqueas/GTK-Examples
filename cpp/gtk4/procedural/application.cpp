#include <print>
#include <gtkmm.h>

static void on_app_activate();
static void on_app_startup();

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Procedural.ApplicationWindow";
static const Glib::ustring APP_TITLE = "Gtk::ApplicationWindow";
static Glib::RefPtr<Gtk::Application> app;

int main(int argc, char** argv) {
  app = Gtk::Application::create(APP_ID);
  app->signal_startup().connect(sigc::ptr_fun(&on_app_startup));
  app->signal_activate().connect(sigc::ptr_fun(&on_app_activate));
  return app->run(argc, argv);
}

static void on_app_activate() {
  std::println("::activate");
}

static void on_app_startup() {
  std::println("::startup");
}