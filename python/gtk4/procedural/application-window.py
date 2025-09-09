import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.Procedural.ApplicationWindow"
APP_TITLE = "Gtk.ApplicationWindow"

def onAppStartup(self):
    global APP_TITLE

    window = Gtk.ApplicationWindow(application = self)
    window.set_title(APP_TITLE)
    window.set_default_size(400, 400)

if __name__ == "__main__":
    app = Gtk.Application(application_id = APP_ID, flags = 0)
    app.connect("activate", lambda self: self.get_active_window().present())
    app.connect("startup", onAppStartup)

    sys.exit(app.run(sys.argv))