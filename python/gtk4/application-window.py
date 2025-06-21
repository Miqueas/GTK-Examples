import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.ApplicationWindow"
appTitle = "GtkApplicationWindow"

def onAppStartup(self):
  window = Gtk.ApplicationWindow(application = self)
  window.set_title(appTitle)
  window.set_default_size(400, 400)

app = Gtk.Application(application_id = appID)
app.connect("activate", lambda self: self.get_active_window().present())
app.connect("startup", onAppStartup)

sys.exit(app.run(sys.argv))