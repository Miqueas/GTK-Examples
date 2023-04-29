local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Image2"
local appTitle = "GtkImage"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local image = Gtk.Image({ visible = true, icon_name = "computer", pixel_size = 256 })

  win:add(image)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)