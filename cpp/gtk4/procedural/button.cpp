#include <print>
#include <gtkmm.h>
#include <iostream>

static void on_app_activate();
static void on_app_startup();

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Procedural.Button";
static const Glib::ustring APP_TITLE = "Gtk::Button";
static Glib::RefPtr<Gtk::Application> app;

int main(int argc, char** argv) {
  app = Gtk::Application::create(APP_ID);
  app->signal_startup().connect(sigc::ptr_fun(&on_app_startup));
  app->signal_activate().connect(sigc::ptr_fun(&on_app_activate));
  return app->run(argc, argv);
}

static void on_app_activate() {
  Gtk::Window* window = app->get_active_window();
  if (window != nullptr) window->present();
}

static void on_app_startup() {
  auto window = Gtk::make_managed<Gtk::ApplicationWindow>(app);
  auto button = Gtk::make_managed<Gtk::Button>("Click Me");

  window->set_child(*button);
  window->set_title(APP_TITLE);
  window->set_default_size(400, 400);

  button->set_halign(Gtk::Align::CENTER);
  button->set_valign(Gtk::Align::CENTER);
  button->signal_clicked().connect([]() {
    std::println("You clicked me!");
  });
}