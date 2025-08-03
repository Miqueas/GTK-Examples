import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.ApplicationWindow"
appTitle = "Gtk.ApplicationWindow"

def onAppStartup(self):
    global appTitle

    window = Gtk.ApplicationWindow(application = self)
    window.set_title(appTitle)
    window.set_default_size(400, 400)

app = Gtk.Application(application_id = appID, flags = 0)
app.connect("activate", lambda self: self.get_active_window().present())
app.connect("startup", onAppStartup)

sys.exit(app.run(sys.argv))