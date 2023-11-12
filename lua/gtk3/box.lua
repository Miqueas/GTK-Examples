local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkBox: An horizontal or vertical layout container

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Box"
local appTitle = "GtkBox"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local headerBar = Gtk.HeaderBar()
  local box = Gtk.Box.new(Gtk.Orientation.VERTICAL, 10)

  window:add(box)
  window:set_titlebar(headerBar)
  window:set_default_size(400, 400)

  headerBar.visible = true
  headerBar.title = appTitle
  headerBar.show_close_button = true

  box.valign = Gtk.Align.CENTER
  box.halign = Gtk.Align.CENTER
  box:pack_start(Gtk.Label.new("A label"), false, true, 0)
  box:pack_start(Gtk.Button.new_with_label("A button"), false, true, 0)
  box:show_all()
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)