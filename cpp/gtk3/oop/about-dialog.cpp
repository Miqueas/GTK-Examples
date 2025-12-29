#include <print>
#include <gtkmm.h>
#include <iostream>

static const Glib::ustring APP_ID = "io.github.Miqueas.GTK-Examples.Cpp.Gtk3.OOP.AboutDialog";
static const Glib::ustring APP_TITLE = "Gtk::AboutDialog";
static const Glib::ustring LICENSE = "Copyright (C) 2021-2025 Josué Martínez\n"
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

class App : public Gtk::Application {
  public:
    static Glib::RefPtr<App> create() {
      return Glib::RefPtr<App>(new App());
    }

  protected:
    App() : Gtk::Application(APP_ID) {}

    void on_activate() override {
      Gtk::Window* window = get_active_window();
      if (!window) return std::println(std::cerr, "No window");

      auto dialog = dynamic_cast<Gtk::Dialog*>(window);
      if (!dialog) return std::println(std::cerr, "Window is not a dialog");

      dialog->run();
      quit();
    }

    void on_startup() override {
      // Ensures chain-up
      Gtk::Application::on_startup();

      auto dialog = new Gtk::AboutDialog();
      dialog->set_modal(true);
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

      add_window(*dialog);
    }
};

int main(int argc, char** argv) {
  return App::create()->run(argc, argv);
}