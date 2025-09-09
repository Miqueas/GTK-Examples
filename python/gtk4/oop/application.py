import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

class App(Gtk.Application):
    APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.OOP.Application"

    def __init__(self):
        super().__init__(application_id = self.APP_ID)

    def do_activate(self):
        print("Gio.Application::activate called")

    def do_startup(self):
        # Ensures chain-up
        Gtk.Application.do_startup(self)
        print("Gio.Application::startup called")

if __name__ == "__main__":
    sys.exit(App().run(sys.argv))