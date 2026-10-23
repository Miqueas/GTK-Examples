#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.Procedural.CheckButton";
static const Glib::ustring APP_TITLE = "Gtk::CheckButton";

static void on_app_activate(Glib::RefPtr<Gtk::Application> self);
static void on_app_startup(Glib::RefPtr<Gtk::Application> self);
static void on_button_selected(Gtk::CheckButton* self);

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(&on_app_activate), app));
  app->signal_startup().connect(sigc::bind(sigc::ptr_fun(&on_app_startup), app));
  return app->run(argc, argv);
}

static void on_app_activate(Glib::RefPtr<Gtk::Application> self) {
  Gtk::Window* window = self->get_active_window();
  if (window) window->show_all();
}

static void on_app_startup(Glib::RefPtr<Gtk::Application> self) {
  Gtk::ApplicationWindow* window = new Gtk::ApplicationWindow(self);
  Gtk::CheckButton* button = new Gtk::CheckButton("OFF");

  window->add(*button);
  window->set_title(APP_TITLE);
  window->set_default_size(400, 400);

  button->set_visible(true);
  button->set_halign(Gtk::ALIGN_CENTER);
  button->set_valign(Gtk::ALIGN_CENTER);
  button->set_active(false);
  button->signal_toggled().connect(sigc::bind(sigc::ptr_fun(&on_button_selected), button));
}

static void on_button_selected(Gtk::CheckButton* self) {
  if (self->get_active()) self->set_label("ON");
  else self->set_label("OFF");
}