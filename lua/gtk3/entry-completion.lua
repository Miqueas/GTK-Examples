local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject", "2.0")

-- GtkEntryCompletion: a helper class for GtkEntry widgets auto-completion

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.EntryCompletion"
local appTitle = "GtkEntryCompletion"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  local items = { "GNOME", "Lua", "LGI", "GTK", "Moonsteal", "Example" }
  local model = Gtk.ListStore.new({ GObject.Type.STRING })

  for _, name in ipairs(items) do
    model:append({ name })
  end

  local entryCompletion = Gtk.EntryCompletion({
    model = model,
    text_column = 0,
    popup_completion = true
  })

  local entry = Gtk.Entry({ visible = true, completion = entryCompletion })

  local box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Try typing \"gnome\" or \"gtk\"" }),
    entry
  })

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)