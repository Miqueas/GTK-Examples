local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkOverlay: a widget for pushing widgets on top of other (like an stack)

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Overlay"
local appTitle = "GtkOverlay"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local overlay = Gtk.Overlay({
    visible = true,

    Gtk.Image({
      visible = true,
      icon_name = "computer",
      pixel_size = 256
    })
  })

  overlay:add_overlay(Gtk.Image({
    visible = true,
    icon_name = "computer-symbolic",
    pixel_size = 128
  }))

  overlay:add_overlay(Gtk.Image({
    visible = true,
    icon_name = "input-gaming",
    pixel_size = 64
  }))

  overlay:add_overlay(Gtk.Image({
    visible = true,
    icon_name = "input-gaming-symbolic",
    pixel_size = 32
  }))

  window:add(overlay)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)