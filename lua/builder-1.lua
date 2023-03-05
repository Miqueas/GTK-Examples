local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkBuilder: Create graphical user interfaces with XML

local app_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Builder1"
local app = Gtk.Application({ application_id = app_id })
local builder = Gtk.Builder.new_from_file("GtkBuilder.ui")

function app:on_startup()
  self:add_window(builder:get_object("window"))
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)