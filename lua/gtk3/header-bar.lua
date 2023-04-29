local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkHeaderBar: a (client-side) title bar decoration widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.HeaderBar"
local appTitle = "GtkHeaderBar"
local appSubtitle = "A (client-side) title bar decoration widget"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })

  local headerBar = Gtk.HeaderBar({
    visible = true,
    -- GtkHeaderBar don't sets the window controls buttons by default
    -- this property changes that behavior
    show_close_button = true,
    title = appTitle,
    subtitle = appSubtitle
  })

  win:set_titlebar(headerBar)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)