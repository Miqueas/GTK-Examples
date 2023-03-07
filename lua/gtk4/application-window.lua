local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- GtkApplicationWindow: A GtkWindow with GtkApplication integration

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.ApplicationWindow"
local appTitle = "GtkApplicationWindow"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  -- Since we're not going to use this window, I don't store it in a variable
  Gtk.ApplicationWindow({
    title = appTitle,
    -- By setting the application to the new window is enough to to present it later
    application = self,
    default_width = 400,
    default_height = 400
  })
end

function app:on_activate()
  -- Because we set the application to the window (line 13), now we have a "default/main"
  -- window to present
  self.active_window:present()
end

return app:run(arg)