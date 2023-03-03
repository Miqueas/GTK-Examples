local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local Builder = Gtk.Builder.new_from_file("GtkBuilder.ui")

-- Another way to use GtkBuilder in LGI
local UI      = Builder.objects
local App     = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Builder2"
})

function App:on_startup()
  self:add_window(UI.Window)
end

function App:on_activate()
  self.active_window:present()
end

return App:run(arg)