import gi
gi.require_version("Gtk", "4.0")
from gi.repository import GLib, Gtk

APP_TITLE = "Gtk.Window"

if __name__ == "__main__":
    window = Gtk.Window()
    window.set_title(APP_TITLE)
    window.set_default_size(400, 400)
    window.present()

    while Gtk.Window.get_toplevels().get_n_items() > 0:
        GLib.MainContext.default().iteration(True)