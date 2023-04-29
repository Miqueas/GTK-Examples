local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkRevealer: a container for show/hide a widget with an animation.

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Revealer"
local appTitle = "GtkRevealer"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 200,
    resizable = false,
    border_width = 10
  })

  local revealer = Gtk.Revealer({
    visible = true,
    reveal_child = true,

    Gtk.Label({ visible = true, label = "Hello there!", margin = 10 })
  })

  local toggleButton = Gtk.ToggleButton({ visible = true, label = "Toggle message", active = revealer.reveal_child })

  function toggleButton:on_clicked()
    revealer.reveal_child = (not revealer.reveal_child) and true or false
  end

  local box = Gtk.Box({ visible = true, orientation = Gtk.Orientation.VERTICAL })
  box:pack_start(revealer, true, true, 0)
  box:pack_start(toggleButton, false, false, 0)

  window:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)