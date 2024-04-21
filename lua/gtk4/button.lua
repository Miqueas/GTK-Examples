local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")
local Gio = lgi.Gio

-- GtkButton: A button widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Button"
local appTitle = "GtkButton"
local app = Gtk.Application.new(appID, Gio.ApplicationFlags.FLAGS_NONE)

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local button = Gtk.Button.new_with_label("Click me!")
  local titelLabel = Gtk.Label.new(([[<span font="bold">%s</span>]]):format(appTitle))
  local headerBar = Gtk.HeaderBar.new()
  local counter = 1

  window.child = button
  window.title = appTitle
  window:set_titlebar(headerBar)
  window:set_default_size(400, 400)

  button.valign = Gtk.Align.CENTER
  button.halign = Gtk.Align.CENTER

  titelLabel.use_markup = true

  headerBar.title_widget = titelLabel
  headerBar.show_title_buttons = true

  -- The "clicked" signal is emited when the user press the button
  function button:on_clicked()
    print(("Clicked %d times!"):format(counter))
    counter = counter + 1
  end
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)