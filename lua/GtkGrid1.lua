local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkGrid1"
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
    subtitle = "Example 1"
  }))

  --[[ GtkGrid:

    A container that acts like a grid, with columns, rows and cells.
    Just look at this example:

  ]]
  local Grid = Gtk.Grid({
    visible = true,
    -- This makes all columns of the same width
    column_homogeneous = true,
    -- Same, but for rows
    row_homogeneous = true,
    -- Sets the spacing between all columns
    column_spacing = 10,
    -- Same, but for rows
    row_spacing = 10,

    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    -- If you can't understand how GtkGrid works, see the GtkGrid-Explained.png file
    { Gtk.Label({ visible = true, label = "Top: 0. Left: 0" }), top_attach = 0, left_attach = 0 },
    { Gtk.Label({ visible = true, label = "Top: 0. Left: 1" }), top_attach = 0, left_attach = 1 },
    { Gtk.Label({ visible = true, label = "Top: 0. Left: 2" }), top_attach = 0, left_attach = 2 },
    { Gtk.Label({ visible = true, label = "Top: 1. Left: 0" }), top_attach = 1, left_attach = 0 },
    { Gtk.Label({ visible = true, label = "Top: 1. Left: 1" }), top_attach = 1, left_attach = 1 },
    { Gtk.Label({ visible = true, label = "Top: 1. Left: 2" }), top_attach = 1, left_attach = 2 },
    { Gtk.Label({ visible = true, label = "Top: 2. Left: 0" }), top_attach = 2, left_attach = 0 },
    { Gtk.Label({ visible = true, label = "Top: 2. Left: 1" }), top_attach = 2, left_attach = 1 },
    { Gtk.Label({ visible = true, label = "Top: 2. Left: 2" }), top_attach = 2, left_attach = 2 }
  })

  self.active_window:add(Grid)
  self.active_window:present()
end

return App:run(arg)