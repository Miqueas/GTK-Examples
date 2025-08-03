import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

# GtkActionBar: A full width container to add contextual actions

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.ActionBar"
appTitle = "Gtk.ActionBar"

def onAppStartup(self):
    global appTitle

    window = Gtk.ApplicationWindow(application = self, title = appTitle)
    actionBar = Gtk.ActionBar()
    box = Gtk.Box(orientation = Gtk.Orientation.VERTICAL)

    window.add(box)
    window.set_default_size(400, 400)

    actionBar.pack_start(Gtk.Label(label = "Something"))
    actionBar.pack_end(Gtk.Button(label = "A button"))

    box.pack_start(Gtk.Label(label = "App content here"), True, True, 0)
    box.pack_end(actionBar, False, False, 0)
    box.show_all()

app = Gtk.Application(application_id = appID, flags = 0)
app.connect("activate", lambda self: self.get_active_window().present())
app.connect("startup", onAppStartup)

sys.exit(app.run(sys.argv))