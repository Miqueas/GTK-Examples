local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Grid3"
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
    subtitle = "Example 3"
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
  })

  for top = 0, 2 do
    for left = 0, 2 do
      Grid:attach(
        Gtk.Label({
          visible = true,
          label = ("Top: %d. Left: %d."):format(top, left)
        }),
        left, top, 1, 1
      )
    end
  end

  self.active_window:add(Grid)
  self.active_window:present()
end

return App:run(arg)