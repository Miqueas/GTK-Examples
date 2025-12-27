#include <gtkmm.h>

static void on_app_startup();
static void on_app_activate();

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.Procedural.ActionBar";
static const Glib::ustring APP_TITLE = "Gtk::ActionBar";
static Glib::RefPtr<Gtk::Application> app;

int main(int argc, char** argv) {
  app = Gtk::Application::create(APP_ID);
  app->signal_startup().connect(sigc::ptr_fun(&on_app_startup));
  app->signal_activate().connect(sigc::ptr_fun(&on_app_activate));
  return app->run(argc, argv);
}

static void on_app_activate() {
  Gtk::Window* window = app->get_active_window();
  if (window) window->present();
}

static void on_app_startup() {
  auto window = Gtk::make_managed<Gtk::ApplicationWindow>(app);
  auto action_bar = Gtk::make_managed<Gtk::ActionBar>();
  auto action_bar_label = Gtk::make_managed<Gtk::Label>("Something");
  auto action_bar_button = Gtk::make_managed<Gtk::Button>("A button");
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 0);
  auto box_label = Gtk::make_managed<Gtk::Label>("App content");

  window->set_child(*box);
  window->set_title(APP_TITLE);
  window->set_default_size(400, 400);

  action_bar->pack_start(*action_bar_label);
  action_bar->pack_end(*action_bar_button);

  box->append(*box_label);
  box->append(*action_bar);

  box_label->set_vexpand(true);
  box_label->set_hexpand(true);
}