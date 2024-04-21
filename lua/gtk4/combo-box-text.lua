local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")
local Gio = lgi.Gio

-- GtkComboBoxText: Just a text-only GtkComboBox

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.ComboBoxText"
local appTitle = "GtkComboBoxText"
local app = Gtk.Application.new(appID, Gio.ApplicationFlags.FLAGS_NONE)
local items = { "GNOME", "KDE Plasma", "XFCE", "MATE", "Cinnamon", "Pantheon", "LXDE", "LXQT" }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local box = Gtk.Box.new(Gtk.Orientation.VERTICAL, 10)
  local label = Gtk.Label.new("Default id: 1")
  local combo = Gtk.ComboBoxText.new()

  window.child = box
  window.title = appTitle
  window:set_default_size(400, 400)

  box.halign = Gtk.Align.CENTER
  box.valign = Gtk.Align.CENTER
  box:append(Gtk.Label.new("Select an option"))
  box:append(combo)
  box:append(label)

  for id, value in ipairs(items) do
    combo:append(id, value)
  end

  combo.active_id = 1

  function combo:on_changed()
    label.label = "Option id: " .. self:get_active_id()
  end
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)