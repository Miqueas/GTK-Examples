local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ListBox1"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkListBox",
    subtitle = "Example 1"
  }))

  local Box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL
  })

  --[[ GtkListBox:

    A container for lists. It works better for lists
    than a GtkBox because of its vertical nature and
    the API it offers.

  ]]
  local List = Gtk.ListBox({ visible = true })

  local Scroll = Gtk.ScrolledWindow({
    visible = true,
    shadow_type = Gtk.ShadowType.NONE,
    propagate_natural_width = true,
    propagate_natural_height = true,

    List
  })

  local Btn = Gtk.Button({
    visible = true,
    label = "Load",
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER
  })

  function Btn:on_clicked()
    for i = 0, 100 do
      List:insert(Gtk.Label({ visible = true, label = "Text " .. i }), i)
    end
  end

  local Box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,

    { Scroll, expand = true },
    { Btn }
  })

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)