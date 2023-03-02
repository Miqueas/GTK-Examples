local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject", "2.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkEntry"
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
    title = "GtkEntry"
  }))

  -- Label to be updated
  local Label = Gtk.Label({ visible = true })

  --[[ GtkEntry:

    An input widget

  ]]
  local Entry = Gtk.Entry({ visible = true })

  -- Updates the label text while typing
  function Entry:on_key_release_event()
    Label.label = Entry.text
  end

  local Box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Enter some text" }),
    Entry,
    Label
  })

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)