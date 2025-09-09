local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")
local GLib = lgi.require("GLib")

local appTitle <const> = "Gtk.Window"
local window = Gtk.Window()
window:set_title(appTitle)
window:set_default_size(400, 400)
window:present()

while Gtk.Window.get_toplevels():get_n_items() > 0 do
  GLib.MainContext.default():iteration(true)
end