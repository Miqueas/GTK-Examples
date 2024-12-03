local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local Gio = lgi.Gio

-- GtkButton: A button widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Button"
local appTitle = "GtkButton"
local app = Gtk.Application.new(appID, Gio.ApplicationFlags.DEFAULT_FLAGS)

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local headerBar = Gtk.HeaderBar()
  local button = Gtk.Button.new_with_label("Click me!")
  local count = 1

  window.child = button
  window.title = appTitle
  window:set_titlebar(headerBar)
  window:set_default_size(400, 400)

  headerBar.title = appTitle
  headerBar.visible = true
  headerBar.show_close_button = true

  button.valign = Gtk.Align.CENTER
  button.halign = Gtk.Align.CENTER
  button.visible = true

  -- The "clicked" signal is emited when the user press the button
  function button:on_clicked()
    self.label = ("Clicked %d times!"):format(count)
    count = count + 1
  end
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)