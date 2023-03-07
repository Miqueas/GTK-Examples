local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject", "2.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Notebook"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })
end

function App:on_activate()
  -- Append button
  local Btn = Gtk.Button({
    visible = true,

    Gtk.Box({
      visible = true,

      Gtk.Image({ visible = true, icon_name = "list-add-symbolic" })
    })
  })

  -- Header bar
  local Header = Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkNotebook",
    subtitle = "Click in the + button!",

    Btn
  })

  self.active_window:set_titlebar(Header)

  --[[ GtkNotebook:

    Similar to a GtkStack, it shows only 1 child at a time,
    but with the difference that it uses "tabs" to switch
    between the visible children.

  ]]
  local Notebook = Gtk.Notebook({
    visible = true,
    -- Removes a default border around the widget
    show_border = false,
    -- If has a lot of tabs, then makes it "scrollable"
    scrollable = true
  })

  local count = 1

  function Btn:on_clicked()
    Notebook:append_page(
      -- Page content
      Gtk.Label({ visible = true, label = "Page " .. count }),
      -- Page tab widget
      Gtk.Label({ visible = true, label = "Tab " .. count })
    )

    count = count + 1
  end

  self.active_window:add(Notebook)
  self.active_window:present()
end

return App:run(arg)