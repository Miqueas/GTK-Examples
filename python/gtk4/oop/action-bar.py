import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

# GtkActionBar: A full width container to add contextual actions

class App(Gtk.Application):
    APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.OOP.ActionBar"
    APP_TITLE = "Gtk.ActionBar"

    def __init__(self):
        super().__init__(application_id = self.APP_ID)

    def do_activate(self):
        window = self.get_active_window()
        if window: window.present()

    def do_startup(self):
        # Ensures chain-up
        Gtk.Application.do_startup(self)
        
        window = Gtk.ApplicationWindow(application = self)
        box = Gtk.Box(orientation = Gtk.Orientation.VERTICAL)
        label = Gtk.Label(label = "App content here", vexpand = True, hexpand = True)
        actionBar = Gtk.ActionBar()

        window.set_child(box)
        window.set_title(self.APP_TITLE)
        window.set_default_size(400, 400)

        box.append(label)
        box.append(actionBar)

        actionBar.pack_start(Gtk.Label(label = "Something"))
        actionBar.pack_end(Gtk.Button(label = "A button"))

if __name__ == "__main__":
    sys.exit(App().run(sys.argv))