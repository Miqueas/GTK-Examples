local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Revealer"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 10
  })
end

function App:on_activate()
  local Header = Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkRevealer"
  })

  local Btn = Gtk.Button({ visible = true, label = "Toggle message" })
  Header:pack_start(Btn)
  self.active_window:set_titlebar(Header)

  local Box = Gtk.Box({ visible = true, orientation = Gtk.Orientation.VERTICAL })

  --[[ GtkRevealer:

    A container for show/hide a widget with animation.

  ]]
  local Rev = Gtk.Revealer({
    visible = true,
    reveal_child = true,

    Gtk.Label({ visible = true, label = "Hello there!", margin = 10 })
  })

  function Btn:on_clicked()
    Rev.reveal_child = (not Rev.reveal_child) and true or false
  end

  Box:pack_start(Rev, false, true, 0)

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)