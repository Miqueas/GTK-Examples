local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Button1"
local appTitle = "GtkButton 1"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local headerBar = Gtk.HeaderBar()
  local button = Gtk.Button.new_with_label("Click me!")
  local counter = 1

  window:add(button)
  window:set_titlebar(headerBar)
  window:set_default_size(400, 400)

  headerBar.visible = true
  headerBar.title = appTitle
  headerBar.show_close_button = true

  button.visible = true
  button.valign = Gtk.Align.CENTER
  button.halign = Gtk.Align.CENTER

  function button:on_clicked()
    print(("Clicked %d times!"):format(counter))
    counter = counter + 1
  end
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)