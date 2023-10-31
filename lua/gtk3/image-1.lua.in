local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkImage: a widget that shows an image

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Image1"
local appTitle = "GtkImage"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local image = Gtk.Image({ visible = true, file = "sus.jpg", pixel_size = 256 })

  win:add(image)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)