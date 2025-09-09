import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

# GtkActionBar: A full width container to add contextual actions

APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.Procedural.ActionBar"
APP_TITLE = "Gtk.ActionBar"

def onAppStartup(self):
    global APP_TITLE

    window = Gtk.ApplicationWindow(application = self, title = APP_TITLE)
    box = Gtk.Box(orientation = Gtk.Orientation.VERTICAL)
    label = Gtk.Label(label = "App content here", vexpand = True, hexpand = True)
    actionBar = Gtk.ActionBar()

    window.set_child(box)
    window.set_title(APP_TITLE)
    window.set_default_size(400, 400)

    actionBar.pack_start(Gtk.Label(label = "Something"))
    actionBar.pack_end(Gtk.Button(label = "A button"))

    box.append(label)
    box.append(actionBar)

if __name__ == "__main__":
    app = Gtk.Application(application_id = APP_ID, flags = 0)
    app.connect("activate", lambda self: self.get_active_window().present())
    app.connect("startup", onAppStartup)

    sys.exit(app.run(sys.argv))