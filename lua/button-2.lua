local lgi = require"lgi"
local Gtk = lgi.require("Gtk", "3.0")

local app_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Button2"
local app_title = "GtkButton 2"
local app = Gtk.Application({ application_id = app_id })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = app_title,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local button = Gtk.Button({
    visible = true,
    label = "Click me!",
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  })

  local counter = 1

  function button:on_clicked()
    self.label = ("Clicked %d times!"):format(counter)
    counter = counter + 1
  end

  win:add(button)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)