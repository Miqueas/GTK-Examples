local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkActionBar: A full width container to add contextual actions.

local app_id = "io.github.Miqueas.Lua-GTK-Examples.Gtk3.ActionBar"
local app_title = "GtkActionBar"
local app = Gtk.Application { application_id = app_id }

function app:on_startup()
  local win = Gtk.ApplicationWindow {
    title = app_title,
    application = self,
    default_width = 400,
    default_height = 400
  }

  local bar = Gtk.ActionBar({ visible = true })
  local box = Gtk.Box({ visible = true, orientation = Gtk.Orientation.VERTICAL })

  bar:pack_start(Gtk.Label({ visible = true, label = "Something" }))
  bar:pack_end(Gtk.Button({ visible = true, label = "A button" }))

  box:pack_start(Gtk.Label({ visible = true, label = "Here is the content of your app" }), true, true, 0)
  box:pack_end(bar, false, true, 0)

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)