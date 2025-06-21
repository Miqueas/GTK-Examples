import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.Application"

app = Gtk.Application(application_id = appID)
app.connect("activate", lambda _: print("app::activate called"))
app.connect("startup", lambda _: print("app::startup called"))

sys.exit(app.run(sys.argv))