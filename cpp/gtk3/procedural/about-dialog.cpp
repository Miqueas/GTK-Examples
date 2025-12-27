#include <gtkmm.h>

const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.Procedural.AboutDialog";
const Glib::ustring APP_TITLE = "Gtk::AboutDialog";
const Glib::ustring LICENSE = "Copyright (C) 2021-2025 Josué Martínez\n"
"\n"
"  This software is provided 'as-is', without any express or implied\n"
"  warranty.  In no event will the authors be held liable for any damages\n"
"  arising from the use of this software.\n"
"\n"
"  Permission is granted to anyone to use this software for any purpose,\n"
"  including commercial applications, and to alter it and redistribute it\n"
"  freely, subject to the following restrictions:\n"
"\n"
"  1. The origin of this software must not be misrepresented; you must not\n"
"     claim that you wrote the original software. If you use this software\n"
"     in a product, an acknowledgment in the product documentation would be\n"
"     appreciated but is not required.\n"
"  2. Altered source versions must be plainly marked as such, and must not be\n"
"     misrepresented as being the original software.\n"
"  3. This notice may not be removed or altered from any source distribution.\0";

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

  if (window) {
    auto dialog = dynamic_cast<Gtk::Dialog*>(window);

    if (dialog) {
      dialog->run();
      self->quit();
    }
  }
}

void on_app_startup(Glib::RefPtr<Gtk::Application> self) {
  // Because `Gtk::AboutDialog` doesn't have a parent widget per se, there's no
  // point in using `Gtk::make_managed()` with it.
  auto dialog = new Gtk::AboutDialog();
  dialog->set_modal(true);
  dialog->set_application(self);
  dialog->set_artists({ "Josué Martínez" });
  dialog->set_authors({ "Josué Martínez" });
  dialog->set_documenters({ "Josué Martínez" });
  dialog->set_translator_credits("Josué Martínez");
  dialog->set_program_name(APP_TITLE);
  dialog->set_comments("GTK+ 3.0 AboutDialog Example");
  dialog->set_copyright("Copyright © 2021-2025 Josué Martínez");
  dialog->set_version("0.1.0");
  dialog->set_license(LICENSE);
  dialog->set_wrap_license(true);
  dialog->set_website("https://github.com/Miqueas/GTK-Examples");
  dialog->set_website_label("GitHub Repository");
}