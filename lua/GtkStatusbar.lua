local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Statusbar"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 200
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkStatusbar"
  }))

  --[[ GtkStatusbar:

    A widget like GtkActionBar for report some info to the user.

  ]]
  local Status = Gtk.Statusbar({ visible = true })

  local Btn = Gtk.Button({
    visible = true,
    label = "Click me",
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER
  })


  local c = 0
  function Btn:on_clicked()
    c = c + 1
    Status:push(c, "You clicked " .. c .. " times")
  end

  local Box = Gtk.Box({ visible = true, orientation = Gtk.Orientation.VERTICAL })
  Box:pack_start(Btn, true, true, 0)
  Box:pack_end(Status, false, true, 0)

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)