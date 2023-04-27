local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- GtkButton: A button widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Button"
local appTitle = "GtkButton"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local button = Gtk.Button({
    label = "Click me!",
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  })

  local counter = 1

  -- The "clicked" signal is emited when the user press the button
  function button:on_clicked()
    print(("Clicked %d times!"):format(counter))
    counter = counter + 1
  end

  win.child = button
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)