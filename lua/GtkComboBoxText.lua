local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject", "2.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkComboBoxText"
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
    title = "GtkComboBoxText"
  }))

  -- Label to be updated
  local Label = Gtk.Label({ visible = true, label = "Default id: gnome" })

  --[[ GtkComboBoxText:

    Just a text-only GtkComboBox

  ]]
  local Combo = Gtk.ComboBoxText({ visible = true })

  local Items = {
    gnome    = "GNOME",
    plasma   = "KDE Plasma",
    xfce     = "XFCE",
    mate     = "MATE",
    cinnamon = "Cinnamon",
    pantheon = "Pantheon",
    lxde     = "LXDE",
    lxqt     = "LXQT"
  }

  for ID, Value in pairs(Items) do
    Combo:append(ID, Value)
  end

  Combo.active_id = "gnome"

  -- Changes the 'Label' text when user change the combo box value
  function Combo:on_changed()
    Label.label = "Option id: " .. self:get_active_id()
  end

  local Box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Select an option" }),
    Combo,
    Label
  })

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)