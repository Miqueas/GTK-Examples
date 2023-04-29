local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkLabel: a text widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Label1"
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
    label = "Hello, world!",
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  })

  win:add(label)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)