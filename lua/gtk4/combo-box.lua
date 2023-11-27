local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")
local GObject = lgi.require("GObject", "2.0")

-- GtkComboBox: A dropdown menu widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.ComboBox"
local appTitle = "GtkComboBox"
local app = Gtk.Application { application_id = appID }
local items = { "GNOME", "KDE Plasma", "XFCE", "MATE", "Cinnamon", "Pantheon", "LXDE", "LXQT" }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local box = Gtk.Box(Gtk.Orientation.VERTICAL, 10)
  local model = Gtk.ListStore.new { GObject.Type.STRING }
  local label = Gtk.Label.new("Default option: 0")
  local comboBox = Gtk.ComboBox.new_with_model(model)

  window.child = box
  window.title = appTitle
  window:set_default_size(400, 400)

  box.halign = Gtk.Align.CENTER
  box.valign = Gtk.Align.CENTER
  box:append(Gtk.Label.new("Select an option"))
  box:append(comboBox)
  box:append(label)

  for _, name in ipairs(items) do
    model:append({ name })
  end

  comboBox.active = 0
  comboBox.cells = { { Gtk.CellRendererText(), { text = 1 }, align = Gtk.Align.START } }

  function comboBox:on_changed()
    local n = self:get_active()
    label.label = "Option " .. n .. " selected (" .. items[n + 1] .. ")"
  end
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)