local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkFileChooserButton: a button that exclusively opens a file selection dialog

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.FileChooserButton"
local appTitle = "GtkFileChooserButton"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  local box = Gtk.Box({
    visible = true,
    spacing = 10,
    orientation = Gtk.Orientation.VERTICAL,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Open a file" }),
  })

  local label = Gtk.Label({ visible = true, wrap = true })

  local fileChooserButton = Gtk.FileChooserButton({
    visible = true,
    halign = Gtk.Align.CENTER
  })

  function fileChooserButton:on_file_set()
    label.label = "Selected file: " .. self:get_filename()
  end

  box:pack_start(fileChooserButton, false, true, 0)
  box:pack_start(label, false, true, 0)

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run()