local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkPaned: a widget with 2 panes and a adjustable division

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Paned"
local appTitle = "GtkPaned"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local paned = Gtk.Paned({ visible = true, orientation = Gtk.Orientation.HORIZONTAL })
  paned:pack1(Gtk.Label({ visible = true, label = "Space 1" }), true, false)
  paned:pack2(Gtk.Label({ visible = true, label = "Space 2" }), true, false)

  window:add(paned)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)