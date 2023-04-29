local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Label2"
local appTitle = "GtkLabel"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local label = Gtk.Label({
    visible = true,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER,
    -- The use_markup property to use an HTML-like
    -- basic markup:
    use_markup = true,
    label = "<span size='xx-large' font_weight='bold'>Hello, world!</span>"
  })

  win:add(label)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)