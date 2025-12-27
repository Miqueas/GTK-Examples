#include <print>
#include <gtkmm.h>
#include <iostream>

static void on_app_startup(Glib::RefPtr<Gtk::Application> self);
static void on_app_activate(Glib::RefPtr<Gtk::Application> self);

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Procedural.AppChooserDialog";
static const Glib::ustring APP_TITLE = "Gtk::AppChooserDialog";

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

static void on_app_activate(Glib::RefPtr<Gtk::Application> self) {
  Gtk::Window* window = self->get_active_window();
  if (!window) return std::println(std::cerr, "No active window found.");

  auto dialog = dynamic_cast<Gtk::AppChooserDialog*>(window);
  if (!dialog) return std::println(std::cerr, "The active window is not an `Gtk::AppChooserDialog`");

  switch (dialog->run()) {
    case Gtk::RESPONSE_OK: {
      Glib::RefPtr<Gio::AppInfo> info = dialog->get_app_info();
      std::println("ID: {}", info->get_id());
      std::println("Executable: {}", info->get_executable());
      std::println("Description: {}", info->get_description());
      std::println("Commandline: {}", info->get_commandline());
      std::println("Display name: {}", info->get_display_name());
      break;
    }
    default: break;
  }

  self->quit();
}

static void on_app_startup(Glib::RefPtr<Gtk::Application> self) {
  // Because `Gtk::AppChooserDialog` doesn't have a parent widget per se, there's
  // no point in using `Gtk::make_managed()` with it.
  auto dialog = new Gtk::AppChooserDialog("image/png");

  dialog->set_title(APP_TITLE);
  dialog->set_application(self);
  dialog->set_border_width(10);
}