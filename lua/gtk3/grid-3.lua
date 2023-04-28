local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Grid3"
local appTitle = "GtkGrid"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  local grid = Gtk.Grid({
    visible = true,
    column_homogeneous = true,
    row_homogeneous = true,
    column_spacing = 10,
    row_spacing = 10,

    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,
  })

  for top = 0, 2 do
    for left = 0, 2 do
      grid:attach(
        Gtk.Label({
          visible = true,
          label = ("Top: %d. Left: %d."):format(top, left)
        }),
        left, top, 1, 1
      )
    end
  end

  win:add(grid)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)