local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkFileChooserButton"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkFileChooserButton"
  }))

  local Box = Gtk.Box({
    visible = true,
    spacing = 10,
    orientation = Gtk.Orientation.VERTICAL,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Open a file" }),
  })

  --[[ GtkFileChooserButton:

    A button that exclusively opens a file selection dialog

  ]]
  local Btn = Gtk.FileChooserButton({
    visible = true,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  })

  local Lbl = Gtk.Label({ visible = true, wrap = true })

  function Btn:on_file_set()
    Lbl.label = "Selected file: " .. self:get_filename()
  end

  Box:pack_start(Btn, false, true, 0)
  Box:pack_start(Lbl, false, true, 0)

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run()