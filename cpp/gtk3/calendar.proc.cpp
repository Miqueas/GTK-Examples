#include <gtkmm.h>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.Procedural.Calendar";
static const Glib::ustring APP_TITLE = "Gtk::Calendar";

static void on_app_activate(Glib::RefPtr<Gtk::Application> self);
static void on_app_startup(Glib::RefPtr<Gtk::Application> self);
static void on_day_selected(Gtk::Calendar* self, Gtk::Label* label);

int main(int argc, char** argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(APP_ID);
  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(&on_app_activate), app));
  app->signal_startup().connect(sigc::bind(sigc::ptr_fun(&on_app_startup), app));
  return app->run(argc, argv);
}

static void on_app_activate(Glib::RefPtr<Gtk::Application> self) {
  auto window = self->get_active_window();
  if (window) window->show_all();
}

static void on_app_startup(Glib::RefPtr<Gtk::Application> self) {
  // Here `Gtk::ApplicationWindow` doesn't have a parent widget, so there's no point in using `Gtk::make_managed()` in
  // this case.
  auto window = new Gtk::ApplicationWindow(self);
  auto box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
  auto calendar = new Gtk::Calendar();
  auto label = new Gtk::Label("Selected data: None");

  window->add(*box);
  window->set_title(APP_TITLE);
  window->set_border_width(10);
  window->set_default_size(400, 400);

  box->pack_start(*calendar, false, false, 0);
  box->pack_start(*label, false, false, 0);
  box->set_halign(Gtk::ALIGN_CENTER);
  box->set_valign(Gtk::ALIGN_CENTER);

  calendar->signal_day_selected().connect(sigc::bind(sigc::ptr_fun(&on_day_selected), calendar, label));
}

static void on_day_selected(Gtk::Calendar* self, Gtk::Label* label) {
  guint year, month, day;

  self->get_date(year, month, day);
  label->set_label("Selected date: " + Glib::DateTime::create_local(year, month, day, 0, 0, 0).format("%d/%m/%Y"));
}