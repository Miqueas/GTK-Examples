local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local window = Gtk.Window()
window.on_destroy = Gtk.main_quit
window:set_default_size(400, 400)
window:present()

Gtk.main()