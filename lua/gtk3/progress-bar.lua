local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ProgressBar"
local appTitle = "GtkProgressBar"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 300,
    default_height = 300,
    border_width = 10
  })

  local progressBar = Gtk.ProgressBar({ show_text = true, pulse_step = 0.2 })
  local pulseButton = Gtk.Button({ label = "Pulse" })
  local fillButton = Gtk.Button({ label = "Fill" })
  local setButton = Gtk.Button({ label = "Set" })

  function pulseButton:on_clicked()
    progressBar:pulse()
  end

  function fillButton:on_clicked()
    progressBar.fraction = 1.0
  end

  function setButton:on_clicked()
    progressBar.fraction = progressBar.fraction + 0.01
  end

  local box = Gtk.Box({
    spacing = 10,
    orientation = Gtk.Orientation.VERTICAL,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER,

    progressBar,
    Gtk.Box({
      spacing = 10,
      orientation = Gtk.Orientation.HORIZONTAL,
      valign = Gtk.Align.CENTER,
      halign = Gtk.Align.CENTER,

      pulseButton,
      fillButton,
      setButton
    })
  })

  box:show_all()
  window:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)