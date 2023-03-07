local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- GtkBox: An horizontal or vertical layout container

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Box"
local app_tile = "GtkBox"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = app_tile,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local box = Gtk.Box({
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    valign = Gtk.Align.CENTER
  })

  box:append(Gtk.Label({ label = "Label 1" }), false, true, 0)
  box:append(Gtk.Label({ label = "Label 2" }), false, true, 0)

  win.child = box
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)