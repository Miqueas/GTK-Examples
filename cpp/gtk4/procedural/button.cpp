#include <print>
#include <gtkmm.h>
#include <iostream>

const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Procedural.Button";
const Glib::ustring APP_TITLE = "Gtk::Button";

void onAppStartup();
void onAppActivate();

Glib::RefPtr<Gtk::Application> app;

int main(int argc, char** argv) {
  app = Gtk::Application::create(APP_ID);
  app->signal_startup().connect(sigc::ptr_fun(&onAppStartup));
  app->signal_activate().connect(sigc::ptr_fun(&onAppActivate));
  return app->run(argc, argv);
}

void onAppActivate() {
  Gtk::Window* window = app->get_active_window();
  if (window != nullptr) window->present();
}

void onAppStartup() {
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