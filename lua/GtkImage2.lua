local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkImage2"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkImage",
    subtitle = "Example 2"
  }))

  local Img = Gtk.Image({ visible = true, icon_name = "computer", pixel_size = 256 })

  self.active_window:add(Img)
  self.active_window:present()
end

return App:run(arg)