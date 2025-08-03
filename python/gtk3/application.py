import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.Application"

app = Gtk.Application(application_id = appID, flags = 0)
app.connect("activate", lambda _: print("app::activate called"))
app.connect("startup", lambda _: print("app::startup called"))

sys.exit(app.run(sys.argv))