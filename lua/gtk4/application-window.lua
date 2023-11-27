local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- GtkApplicationWindow: A GtkWindow with GtkApplication integration

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.ApplicationWindow"
local appTitle = "GtkApplicationWindow"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  window.title = appTitle
  window:set_default_size(400, 400)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)