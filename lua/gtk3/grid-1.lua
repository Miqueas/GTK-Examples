local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkGrid: a container that acts like a grid, with columns, rows and cells

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Grid1"
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

  win:add(grid)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)