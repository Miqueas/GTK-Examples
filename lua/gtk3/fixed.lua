local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkFixed: a widget that can place widgets at fixed positions and fixed sizes

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Fixed"
local appTitle = "GtkFixed"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  local fixed = Gtk.Fixed({
    visible = true,

    { Gtk.Label { visible = true, label = "A" }, y = 20, x = 10 },
    { Gtk.Label { visible = true, label = "B" }, y = 200, x = 100 },
    { Gtk.Label { visible = true, label = "C" }, y = 99, x = 326 }
  })

  win:add(fixed)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)