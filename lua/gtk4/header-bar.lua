local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.HeaderBar"
local appTitle = "<span weight='bold'>GtkHeaderBar</span>"
local appSubtitle = "A (client-side) window decoration widget"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })

  local titleLabel = Gtk.Label({ label = appTitle, use_markup = true })
  local subtitleLabel = Gtk.Label({ label = appSubtitle })
  local titleBox = Gtk.Box({
    orientation = Gtk.Orientation.VERTICAL,
    margin_top = 4,
    margin_bottom = 4,
    valign = Gtk.Align.CENTER
  })

  titleBox:append(titleLabel)
  titleBox:append(subtitleLabel)

  local header = Gtk.HeaderBar({
    -- GtkHeaderBar don't sets the window controls buttons by default
    -- this property changes that behavior
    show_title_buttons = true,
    title_widget = titleBox
  })

  window.titlebar = header
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)