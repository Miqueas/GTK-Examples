local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Overlay"
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
    title = "GtkOverlay"
  }))

  --[[ GtkOverlay:

    A widget that allows widgets on top of other (like an stack). GtkOverlay can have
    only one main (child) widget, trying to add another widget using the 'add()'
    method will throw an error. Use 'add_overlay()' instead, that put the given widget
    on top of the main widget or another widget.

  ]]
  local Overlay = Gtk.Overlay({
    visible = true,

    -- Our main widget
    Gtk.Image({
      visible = true,
      icon_name = "computer",
      pixel_size = 256
    })
  })

  Overlay:add_overlay(Gtk.Image({
    visible = true,
    icon_name = "computer-symbolic",
    pixel_size = 128
  }))

  Overlay:add_overlay(Gtk.Image({
    visible = true,
    icon_name = "input-gaming",
    pixel_size = 64
  }))

  Overlay:add_overlay(Gtk.Image({
    visible = true,
    icon_name = "input-gaming-symbolic",
    pixel_size = 32
  }))

  self.active_window:add(Overlay)
  self.active_window:present()
end

return App:run(arg)