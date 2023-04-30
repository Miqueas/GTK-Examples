local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Statusbar"
local appTitle = "GtkStatusbar"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle, 
    application = self,
    default_width = 400,
    default_height = 200
  })

  local statusbar = Gtk.Statusbar({ visible = true })

  local button = Gtk.Button({
    visible = true,
    label = "Click me",
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER
  })


  local c = 0

  function button:on_clicked()
    c = c + 1
    statusbar:push(c, "You clicked " .. c .. " times")
  end

  local box = Gtk.Box({ visible = true, orientation = Gtk.Orientation.VERTICAL })
  box:pack_start(button, true, true, 0)
  box:pack_end(statusbar, false, true, 0)

  window:add(box)
end

function app:on_activate()
  --[[ GtkStatusbar: A widget like GtkActionBar for report some info to the user.

  ]]
  self.active_window:present()
end

return app:run(arg)