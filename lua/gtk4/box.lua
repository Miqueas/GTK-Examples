local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- GtkBox: An horizontal or vertical layout container

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Box"
local app_tile = "GtkBox"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local box = Gtk.Box.new(Gtk.Orientation.VERTICAL, 10)

  window.child = box
  window.title = app_tile
  window:set_default_size(400, 400)

  box.valign = Gtk.Align.CENTER
  box:append(Gtk.Label.new("Label 1"))
  box:append(Gtk.Label.new("Label 2"))
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)