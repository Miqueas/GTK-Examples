local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkBox1"
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
    title = "GtkBox",
    subtitle = "Example 1"
  }))

  --[[ GtkBox:

    A container thats organize widgets lineal in one of these directions:
      - Vertical
      - Horizontal

  ]]
  local Box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    valign = Gtk.Align.CENTER
  })

  Box:pack_start(
    Gtk.Label({ visible = true, label = "Label 1" }),
    false,
    true,
    0
  )

  Box:pack_start(
    Gtk.Label({ visible = true, label = "Label 2" }),
    false,
    true,
    0
  )

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)