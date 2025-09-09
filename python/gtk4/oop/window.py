import gi
gi.require_version("Gtk", "4.0")
from gi.repository import GLib, Gtk

class Window(Gtk.Window):
    APP_TITLE = "Gtk.Window"

    def __init__(self):
        super().__init__()
        self.set_title(self.APP_TITLE)
        self.set_default_size(400, 400)
        self.present()

if __name__ == "__main__":
    Window()

    while Gtk.Window.get_toplevels().get_n_items() > 0:
        GLib.MainContext.default().iteration(True)