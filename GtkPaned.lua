local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkPaned"
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
    title = "GtkPaned"
  }))

  --[[ GtkPaned:

    A widget with two adjustable panes

  ]]
  local Paned = Gtk.Paned({ visible = true, orientation = Gtk.Orientation.HORIZONTAL })
  Paned:pack1(Gtk.Label({ visible = true, label = "Space 1" }), true, false)
  Paned:pack2(Gtk.Label({ visible = true, label = "Space 2" }), true, false)

  self.active_window:add(Paned)
  self.active_window:present()
end

return App:run(arg)