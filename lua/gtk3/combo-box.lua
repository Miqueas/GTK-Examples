local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject", "2.0")

-- GtkComboBox: A dropdown menu widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ComboBox"
local appTitle = "GtkComboBox"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  -- Model for the combo box
  local model = Gtk.ListStore.new({ GObject.Type.STRING })
  local items = { "GNOME", "KDE Plasma", "XFCE", "MATE", "Cinnamon", "Pantheon", "LXDE", "LXQT" }

  -- Add the items to the model
  for _, name in ipairs(items) do
    model:append({ name })
  end

  -- Label to be updated
  local label = Gtk.Label({ visible = true, label = "Default option: 0" })

  local combo = Gtk.ComboBox({
    visible = true,
    model = model,
    active = 0,
    cells = {
      {
        Gtk.CellRendererText(),
        { text = 1 },
        align = Gtk.Align.START
      }
    }
  })

  -- Changes the 'label' text when user change the combo box value
  function combo:on_changed()
    local n = self:get_active()
    label.label = "Option "..n.." selected ("..items[n + 1]..")"
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

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)