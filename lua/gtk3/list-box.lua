local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkListBox: a list container widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ListBox1"
local appTitle = "GtkListBox"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  local listBox = Gtk.ListBox({ visible = true })

  local scrolledWindow = Gtk.ScrolledWindow({
    visible = true,
    shadow_type = Gtk.ShadowType.NONE,
    propagate_natural_width = true,
    propagate_natural_height = true,

    listBox
  })

  local button = Gtk.Button({
    visible = true,
    label = "Load",
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER
  })

  function button:on_clicked()
    for i = 0, 100 do
      listBox:insert(Gtk.Label({ visible = true, label = "Text " .. i }), i)
    end
  end

  local box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,

    { scrolledWindow, expand = true },
    { button }
  })

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)