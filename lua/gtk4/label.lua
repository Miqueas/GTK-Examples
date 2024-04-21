local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")
local Gio = lgi.Gio

-- GtkLabel: A text widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Label"
local appTitle = "GtkLabel"
local app = Gtk.Application.new(appID, Gio.ApplicationFlags.FLAGS_NONE)

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local label = Gtk.Label.new("Hi there!")

  window.child = label
  window.title = appTitle
  window:set_default_size(400, 400)

  label.valign = Gtk.Align.CENTER
  label.halign = Gtk.Align.CENTER
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)