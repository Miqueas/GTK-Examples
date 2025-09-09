import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

class App(Gtk.Application):
    APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.OOP.Application"
    APP_TITLE = "Gtk.ApplicationWindow"

    def __init__(self):
        super().__init__(application_id = self.APP_ID)

    def do_activate(self):
        window = self.get_active_window()
        if window: window.present()

    def do_startup(self):
        # Ensures chain-up
        Gtk.Application.do_startup(self)
        
        window = Gtk.ApplicationWindow(application = self)
        window.set_title(self.APP_TITLE)
        window.set_default_size(400, 400)

if __name__ == "__main__":
    sys.exit(App().run(sys.argv))