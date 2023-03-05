local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local app = Gtk.Application { application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Fixed" }

function app:on_activate()
  self.active_window:present()
end

function app:on_startup()
  local win = Gtk.ApplicationWindow {
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  }

  win:set_titlebar(Gtk.HeaderBar {
    visible = true,
    show_close_button = true,
    title = "GtkFlowBox"
  })

  local fixed = Gtk.Fixed {
    visible = true,

    { Gtk.Label { visible = true, label = "A" }, y = 20, x = 10 },
    { Gtk.Label { visible = true, label = "B" }, y = 200, x = 100 },
    { Gtk.Label { visible = true, label = "C" }, y = 99, x = 326 }
  }

  win:add(fixed)
end

return app:run(arg)