local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkApplicationWindow: A GtkWindow with GtkApplication integration

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ApplicationWindow"
local appTitle = "GtkApplicationWindow"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow()
  local headerBar = Gtk.HeaderBar()

  self:add_window(window)

  window:set_titlebar(headerBar)
  window:set_default_size(400, 400)

  headerBar.visible = true
  headerBar.title = appTitle
  headerBar.show_close_button = true
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)