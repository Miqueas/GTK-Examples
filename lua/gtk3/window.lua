local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkWindow: a window widget

local window = Gtk.Window({
  default_width = 400,
  default_height = 400
})

-- The "destroy" signal is emited when the user clicks the close button
window.on_destroy = Gtk.main_quit
window:present()

Gtk.main()