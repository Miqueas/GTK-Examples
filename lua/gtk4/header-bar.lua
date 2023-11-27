local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.HeaderBar"
local appTitle = "GtkHeaderBar"
local appSubtitle = "App subtitle"
local app = Gtk.Application { application_id = appID }

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local titleLabel = Gtk.Label.new(appTitle)
  local subtitleLabel = Gtk.Label.new(appSubtitle)
  local titleBox = Gtk.Box.new(Gtk.Orientation.VERTICAL, 0)
  local headerBar = Gtk.HeaderBar()

  window.titlebar = headerBar
  window:set_default_size(400, 400)

  titleLabel:add_css_class("title")
  subtitleLabel:add_css_class("subtitle")

  titleBox.valign = Gtk.Align.CENTER
  titleBox:append(titleLabel)
  titleBox:append(subtitleLabel)

  headerBar.title_widget = titleBox
  headerBar.show_title_buttons = true
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)