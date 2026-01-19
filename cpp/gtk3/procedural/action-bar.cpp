#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.Procedural.ActionBar";
static const Glib::ustring APP_TITLE = "Gtk::ActionBar";

static void on_app_activate(const Glib::RefPtr<Gtk::Application>& self);
static void on_app_startup(const Glib::RefPtr<Gtk::Application>& self);

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);
  app->signal_startup().connect(sigc::bind(sigc::ptr_fun(&on_app_startup), app));
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(&on_app_activate), app));
  return app->run(argc, argv);
}

static void on_app_activate(const Glib::RefPtr<Gtk::Application>& self) {
  Gtk::Window* window = self->get_active_window();
  if (window) window->present();
}

static void on_app_startup(const Glib::RefPtr<Gtk::Application>& self) {
  // Because Gtk::ApplicationWindow doesn't have a parent widget per se, there's
  // no point in using Gtk::make_managed() with it.
  Gtk::ApplicationWindow* window = new Gtk::ApplicationWindow(self);
  Gtk::ActionBar* action_bar = Gtk::make_managed<Gtk::ActionBar>();
  Gtk::Label* action_bar_label = Gtk::make_managed<Gtk::Label>("Something");
  Gtk::Button* action_bar_button = Gtk::make_managed<Gtk::Button>("A button");
  Gtk::Box* box = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 0);
  Gtk::Label* box_label = Gtk::make_managed<Gtk::Label>("App content");

  window->add(*box);
  window->set_title(APP_TITLE);
  window->set_default_size(400, 400);

  action_bar->pack_start(*action_bar_label);
  action_bar->pack_end(*action_bar_button);

  box->pack_start(*box_label, true, true, 0);
  box->pack_end(*action_bar, false, true, 0);
  box->show_all();
}