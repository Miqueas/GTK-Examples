local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Label2"
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
    title = "GtkLabel",
    subtitle = "Example 2"
  }))

  local Label = Gtk.Label({
    visible = true,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER,
    -- The use_markup property to use an HTML-like
    -- basic markup:
    use_markup = true,
    label = "<span size='xx-large' font_weight='bold'>Hello, world!</span>"
  })

  self.active_window:add(Label)
  self.active_window:present()
end

return App:run(arg)