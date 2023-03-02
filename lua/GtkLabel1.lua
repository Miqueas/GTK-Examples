local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkLabel1"
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
    title = "GtkLabel",
    subtitle = "Example 1"
  }))

  --[[ GtkLabel:

    A text widget

  ]]
  local Label = Gtk.Label({
    visible = true,
    label = "Hello, world!",
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  })

  self.active_window:add(Label)
  self.active_window:present()
end

return App:run(arg)