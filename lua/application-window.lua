local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkApplicationWindow: A GtkWindow with GtkApplication integration

local app_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ApplicationWindow"
local app = Gtk.Application({ application_id = app_id })

function app:on_startup()
  -- Since we're not going to use this window, I don't store it in a variable
  Gtk.ApplicationWindow({
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