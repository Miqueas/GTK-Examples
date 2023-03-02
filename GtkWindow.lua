local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

--[[ GtkWindow:

  Well... A window lmao

]]
local Window = Gtk.Window({
  default_width = 400,
  default_height = 400
})

-- The "destroy" signal is emited when the user clicks in the
-- close button
Window.on_destroy = Gtk.main_quit
Window:present()

Gtk.main()