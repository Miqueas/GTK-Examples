#include <gtkmm.h>
#include <iostream>

const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Procedural.ApplicationWindow";
const Glib::ustring APP_TITLE = "Gtk::ApplicationWindow";

static void on_app_activate(Glib::RefPtr<Gtk::Application> self);
static void on_app_startup(Glib::RefPtr<Gtk::Application> self);

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);

  app->signal_startup().connect(sigc::bind<Glib::RefPtr<Gtk::Application>>(
    sigc::ptr_fun(&on_app_startup),
    app
  ));

  app->signal_activate().connect(sigc::bind<Glib::RefPtr<Gtk::Application>>(
    sigc::ptr_fun(&on_app_activate),
    app
  ));

  return app->run(argc, argv);
}

void on_app_activate(Glib::RefPtr<Gtk::Application> self) {
  Gtk::Window* window = self->get_active_window();
  if (window != nullptr) window->present();
}

void on_app_startup(Glib::RefPtr<Gtk::Application> self) {
  // Because Gtk::ApplicationWindow doesn't have a parent widget per se, there's
  // no point in using Gtk::make_managed() with it.
  auto window = new Gtk::ApplicationWindow(self);
  window->set_title(APP_TITLE);
  window->set_default_size(400, 400);
}