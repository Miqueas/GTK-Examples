local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject", "2.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkComboBox"
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
    title = "GtkComboBox"
  }))

  -- Model for the combo box
  local Model = Gtk.ListStore.new({ GObject.Type.STRING })
  local Items = { "GNOME", "KDE Plasma", "XFCE", "MATE", "Cinnamon", "Pantheon", "LXDE", "LXQT" }

  -- Add the items to the model
  for _, Name in ipairs(Items) do
    Model:append({ Name })
  end

  -- Label to be updated
  local Label = Gtk.Label({ visible = true, label = "Default option: 0" })

  --[[ GtkComboBox:

    A container that allows the user to select "something" among several
    valid options.

  ]]
  local Combo = Gtk.ComboBox({
    visible = true,
    model = Model,
    active = 0,
    cells = {
      {
        Gtk.CellRendererText(),
        { text = 1 },
        align = Gtk.Align.START
      }
    }
  })

  -- Changes the 'Label' text when user change the combo box value
  function Combo:on_changed()
    local n = self:get_active()
    Label.label = "Option "..n.." selected ("..Items[n + 1]..")"
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