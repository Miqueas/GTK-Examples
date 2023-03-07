local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- Another way to use GtkBuilder in LGI

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Builder2"
local app = Gtk.Application({ application_id = appID })
local builder = Gtk.Builder.new_from_file("builder.ui")
local ui = builder.objects

function app:on_startup()
  self:add_window(ui.window)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)