local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkBuilder: Create graphical user interfaces with XML

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Builder1"
local app = Gtk.Application({ application_id = appID })
local builder = Gtk.Builder.new_from_file("builder.ui")

function app:on_startup()
  self:add_window(builder:get_object("window"))
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)