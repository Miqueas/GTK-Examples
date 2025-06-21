import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

window = Gtk.Window()
window.connect("destroy", Gtk.main_quit)
window.set_default_size(400, 400)
window.present()

Gtk.main()