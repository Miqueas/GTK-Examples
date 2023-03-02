
if arg[#arg] == "-debug" then require"mobdebug".start() end

local lgi = require"lgi"
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application{
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkButton2"
}

function App:on_startup()
  Gtk.ApplicationWindow{
    application = self,
    default_width = 400,
    default_height = 400
  }
end

function App:on_activate()
  local window = self.active_window
  
  window:set_titlebar(Gtk.HeaderBar{
    visible = true,
    show_close_button = true,
    title = "GtkButton",
    subtitle = "Example 2"
  })

  local Button = Gtk.Button{
    visible = true,
    label = "Click me!",
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  }

  local Notification_ID = 1

  function Button:on_clicked()
    
    local label = ("Clicked %d times!"):format(Notification_ID)
    self.label = label
    print(label)

    if Notification_ID >= 3 then window:destroy() end

    Notification_ID = Notification_ID + 1
    
  end

  window:add(Button)
  window:present()
end

return App:run(arg)