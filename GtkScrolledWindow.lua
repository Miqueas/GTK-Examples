local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkScrolledWindow"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkScrolledWindow"
  }))

  local Grid = Gtk.Grid({
    visible = true,
    column_homogeneous = true,
    row_homogeneous = true,
    column_spacing = 10,
    row_spacing = 10,
    halign = Gtk.Align.START,
    valign = Gtk.Align.START
  })

  --[[ GtkScrolledWindow:

    A container for scrollable content

  ]]
  local Scroll = Gtk.ScrolledWindow({
    visible = true,
    -- Removes a shadow that is added by default
    shadow_type = Gtk.ShadowType.NONE,
    -- "Expands" the child width, and makes the child use the real allocated width
    propagate_natural_width = true,
    -- Same, but for height
    propagate_natural_height = true,

    Grid
  })

  for top = 1, 100 do
    for left = 1, 100 do
      Grid:attach(
        Gtk.Label({ visible = true, label = "Top: "..top..". Left: "..left }),
        left - 1,
        top - 1,
        1, 1
      )
    end
  end

  self.active_window:add(Scroll)
  self.active_window:present()
end

return App:run(arg)