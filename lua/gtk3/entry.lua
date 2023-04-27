local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkEntry: a generic input widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Entry"
local appTitle = "GtkEntry"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  local label = Gtk.Label({ visible = true })
  local entry = Gtk.Entry({ visible = true })

  -- Updates the label text while typing
  function entry:on_key_release_event()
    label.label = entry.text
  end

  local box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Enter some text" }),
    entry,
    label
  })

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)