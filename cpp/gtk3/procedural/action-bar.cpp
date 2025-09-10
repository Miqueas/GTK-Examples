#include <print>
#include <gtkmm.h>
#include <iostream>

const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Procedural.Button";
const Glib::ustring APP_TITLE = "Gtk::ActionBar";

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
  if (window) window->present();
}

void onAppStartup() {
  // Because Gtk::ApplicationWindow doesn't have a parent widget per se, there's
  // no point in using Gtk::make_managed() with it.
  auto window = new Gtk::ApplicationWindow(app);
  auto action_bar = Gtk::make_managed<Gtk::ActionBar>();
  auto action_bar_label = Gtk::make_managed<Gtk::Label>("Something");
  auto action_bar_button = Gtk::make_managed<Gtk::Button>("A button");
  auto box = Gtk::make_managed<Gtk::Box>(
    Gtk::Orientation::ORIENTATION_VERTICAL,
    0
  );
  auto box_label = Gtk::make_managed<Gtk::Label>("App content");

  window->add(*box);
  window->set_title(APP_TITLE);
  window->set_default_size(400, 400);

  action_bar->pack_start(*action_bar_label);
  action_bar->pack_end(*action_bar_button);

  box->pack_start(*box_label, true, true, 0);
  box->pack_end(*action_bar, false, true, 0);
  box->show_all();
}