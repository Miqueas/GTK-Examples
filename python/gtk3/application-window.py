import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.ApplicationWindow"
appTitle = "GtkApplicationWindow"
app = Gtk.Application(application_id = appID)

def onAppStartup(self):
  window = Gtk.ApplicationWindow(application = self)
  window.set_title(appTitle)
  window.set_default_size(400, 400)

app.connect("activate", lambda self: self.get_active_window().present())
app.connect("startup", onAppStartup)

sys.exit(app.run(sys.argv))