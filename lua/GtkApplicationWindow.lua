local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ApplicationWindow"
})

function App:on_startup()
  --[[ GtkApplicationWindow:

    A GtkWindow thats has a better integration with GtkApplication

  ]]
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })
end

function App:on_activate()
  self.active_window:present()
end

return App:run(arg)