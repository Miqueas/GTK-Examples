local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkActionBar: A full width container to add contextual actions

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ActionBar"
local appTitle = "GtkActionBar"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow()
  local headerBar = Gtk.HeaderBar()
  local actionBar = Gtk.ActionBar()
  local mainBox = Gtk.Box()

  self:add_window(window)

  window:set_titlebar(headerBar)
  window:set_default_size(400, 400)
  window:add(mainBox)

  headerBar.visible = true
  headerBar.title = appTitle
  headerBar.show_close_button = true

  actionBar:pack_start(Gtk.Label.new("Something" ))
  actionBar:pack_end(Gtk.Button.new_with_label("A button"))

  mainBox.orientation = Gtk.Orientation.VERTICAL
  mainBox:pack_start(Gtk.Label.new("Here is the content of your app"), true, true, 0)
  mainBox:pack_end(actionBar, false, true, 0)
  mainBox:show_all()
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)