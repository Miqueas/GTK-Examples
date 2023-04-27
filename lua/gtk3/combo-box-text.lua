local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ComboBoxText"
local appTitle = "GtkComboBoxText"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  -- Label to be updated
  local label = Gtk.Label({ visible = true, label = "Default id: gnome" })

  --[[ GtkComboBoxText:

    Just a text-only GtkComboBox

  ]]
  local combo = Gtk.ComboBoxText({ visible = true })

  local Items = {
    "GNOME",
    "KDE Plasma",
    "XFCE",
    "MATE",
    "Cinnamon",
    "Pantheon",
    "LXDE",
    "LXQT"
  }

  for id, value in pairs(Items) do
    -- For GtkComboBoxText, the ID can be either a number or text
    combo:append(id, value)
  end

  combo.active_id = 1

  -- Changes the 'Label' text when user change the combo box value
  function combo:on_changed()
    label.label = "Option id: " .. self:get_active_id()
  end

  local box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Select an option" }),
    combo,
    label
  })

  window:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)