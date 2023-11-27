local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- GtkButton: A button widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Button"
local appTitle = "GtkButton"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local button = Gtk.Button.new("Click me!")
  local counter = 1

  window.child = button
  window.title = appTitle
  window:set_default_size(400, 400)

  button.valign = Gtk.Align.CENTER
  button.halign = Gtk.Align.CENTER

  -- The "clicked" signal is emited when the user press the button
  function button:on_clicked()
    print(("Clicked %d times!"):format(counter))
    counter = counter + 1
  end
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)