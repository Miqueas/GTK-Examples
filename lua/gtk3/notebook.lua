local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Notebook"
local appTitle = "GtkNotebook"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local newTabButton = Gtk.Button({
    visible = true,
    halign = Gtk.Align.CENTER,
    margin = 10,

    Gtk.Box({
      visible = true,
      spacing = 6,
      orientation = Gtk.Orientation.HORIZONTAL,

      Gtk.Label({ visible = true, label = "New tab" }),
      Gtk.Image({ visible = true, icon_name = "list-add-symbolic" })
    })
  })

  local notebook = Gtk.Notebook({
    visible = true,
    -- Removes a default border around the widget
    show_border = false,
    -- If has a lot of tabs, then makes it "scrollable"
    scrollable = true
  })

  local count = 1

  function newTabButton:on_clicked()
    notebook:append_page(
      -- Page content
      Gtk.Label({ visible = true, label = "Page " .. count }),
      -- Page tab widget
      Gtk.Label({ visible = true, label = "Tab " .. count })
    )

    count = count + 1
  end

  local box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL
  })

  box:pack_start(notebook, true, true, 0)
  box:pack_start(newTabButton, false, false, 0)

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)