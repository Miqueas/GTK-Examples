local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject", "2.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkEntryCompletion"
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
    title = "GtkEntryCompletion"
  }))

  -- Model for the entry completion
  local Model = Gtk.ListStore.new({ GObject.Type.STRING })

  -- Items to be completed
  local Items = { "GNOME", "Lua", "LGI", "GTK", "Moonsteal", "Example" }

  -- Add the items to the model
  for _, Name in ipairs(Items) do Model:append({ Name }) end

  -- The entry completion
  local Completion = Gtk.EntryCompletion({
    model = Model,
    text_column = 0,
    popup_completion = true
  })

  -- The entry
  local Entry = Gtk.Entry({ visible = true, completion = Completion })

  local Box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Try \"gnome\" or \"gtk\"" }),
    Entry
  })

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)