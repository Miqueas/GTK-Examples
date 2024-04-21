local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")
local Gio = lgi.Gio

-- GtkActionBar: A full width container to add contextual actions

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.ActionBar"
local appTitle = "GtkActionBar"
local app = Gtk.Application.new(appID, Gio.ApplicationFlags.FLAGS_NONE)

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local titleLabel = Gtk.Label.new(([[<span font="bold">%s</span>]]):format(appTitle))
  local headerBar = Gtk.HeaderBar.new()
  local actionBar = Gtk.ActionBar.new()
  local content = Gtk.Label.new("Here is the content of your app")
  local mainBox = Gtk.Box()

  self:add_window(window)

  window.child = mainBox
  window:set_titlebar(headerBar)
  window:set_default_size(400, 400)

  titleLabel.use_markup = true

  headerBar.title_widget = titleLabel
  headerBar.show_title_buttons = true

  actionBar:pack_start(Gtk.Label.new("Something"))
  actionBar:pack_end(Gtk.Button.new_with_label("A button"))

  content.vexpand = true

  mainBox.orientation = Gtk.Orientation.VERTICAL
  mainBox:append(content)
  mainBox:append(actionBar)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)