local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Grid2"
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

    { Gtk.Label({ visible = true, label = "Columns" }), top_attach = 0, left_attach = 1, width = 2 },
    { Gtk.Label({ visible = true, label = "Rows" }), top_attach = 0, left_attach = 0, height = 3 },
    { Gtk.Label({ visible = true, label = "Top: 1. Left: 1" }), top_attach = 1, left_attach = 1 },
    { Gtk.Label({ visible = true, label = "Top: 1. Left: 2" }), top_attach = 1, left_attach = 2 },
    { Gtk.Label({ visible = true, label = "Top: 2. Left: 1" }), top_attach = 2, left_attach = 1 },
    { Gtk.Label({ visible = true, label = "Top: 2. Left: 2" }), top_attach = 2, left_attach = 2 }
  })

  win:add(grid)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)