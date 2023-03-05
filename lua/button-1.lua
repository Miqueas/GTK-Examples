local lgi  = require("lgi")
local Gtk  = lgi.require("Gtk", "3.0")
local Gio  = lgi.require("Gio", "2.0")
local GLib = lgi.require("GLib", "2.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Button1"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkButton",
    subtitle = "Example 1"
  }))

  --[[ GtkButton:

    Just a button lol

  ]]
  local Button = Gtk.Button({
    visible = true,
    label = "Click me!",
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER
  })

  local Notification_ID = 0

  --for k, v in pairs(GLib:_resolve(true)._struct) do print(k, v) end

  -- The "clicked" signal is emited when the user clicks
  -- the button
  function Button:on_clicked()
    -- Notifications are not yet supported on Windows
    if GLib.get_os_info("ID") == "windows" then
      print(("Clicked %d times!"):format(Notification_ID))
    else
      local Notification = Gio.Notification()
      Notification:set_title("GtkButton example 1")
      Notification:set_body("You cliked the button!")

      -- 'self' can't be used here, because 'self' here
      -- reffers to the GtkButton that's clicked
      App:send_notification(Notification_ID, Notification)
    end

    -- Incrementing this value makes the app spawn various
    -- notifications
    Notification_ID = Notification_ID + 1
  end

  self.active_window:add(Button)
  self.active_window:present()
end

return App:run(arg)