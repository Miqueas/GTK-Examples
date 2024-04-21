local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")
local Gio = lgi.Gio

-- GtkApplicationWindow: A GtkWindow with GtkApplication integration

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.ApplicationWindow"
local appTitle = "GtkApplicationWindow"
local app = Gtk.Application.new(appID, Gio.ApplicationFlags.FLAGS_NONE)

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  window.title = appTitle
  window:set_default_size(400, 400)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)