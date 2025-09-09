import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.Procedural.Application"

app = Gtk.Application(application_id = appID, flags = 0)
app.connect("activate", lambda _: print("Gio.Application::activate called"))
app.connect("startup", lambda _: print("Gio.Application::startup called"))

sys.exit(app.run(sys.argv))