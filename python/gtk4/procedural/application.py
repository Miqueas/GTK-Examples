import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.Procedural.Application"

if __name__ == "__main__":
    app = Gtk.Application(application_id = APP_ID, flags = 0)
    app.connect("activate", lambda _: print("Gio.Application::activate called"))
    app.connect("startup", lambda _: print("Gio.Application::startup called"))

    sys.exit(app.run(sys.argv))