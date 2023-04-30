local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Spinner"
local appTitle = "GtkSpinner"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 300,
    default_height = 300,
    border_width = 10
  })

  local spinner = Gtk.Spinner({ visible = true })
  local button = Gtk.Button({ visible = true, label = "Start" })

  function button:on_clicked()
    if spinner.active then
      self.label = "Start"
      spinner:stop()
    else
      self.label = "Stop"
      spinner:start()
    end
  end

  local box = Gtk.Box({
    visible = true,
    spacing = 10,
    orientation = Gtk.Orientation.VERTICAL,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER,

    spinner,
    button
  })

  window:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)