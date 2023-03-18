local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- GtkLabel: A text widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Label"
local appTitle = "GtkLabel"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local label = Gtk.Label({
    label = "Hi there!",
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  })

  window.child = label
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)