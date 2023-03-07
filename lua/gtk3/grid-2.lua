local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Grid2"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkGrid",
    subtitle = "Example 2"
  }))

  --[[

    In the example GtkGrid1.lua you see a basic grid. Here, you can see a little complex
    grid with two items that fills more than 1 cell in the grid.

  ]]
  local Grid = Gtk.Grid({
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

  self.active_window:add(Grid)
  self.active_window:present()
end

return App:run(arg)