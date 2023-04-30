local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Stack2"
local appTitle = ""
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 600,
    default_height = 400
  })

  local stack = Gtk.Stack({
    visible = true,
    transition_type = Gtk.StackTransitionType.SLIDE_UP_DOWN,
    -- Increment this value to see the animation more slow
    transition_duration = 280,

    {
      Gtk.Label({
        visible = true,
        label = "<span size='xx-large' font_weight='bold'>Page 0</span>",
        use_markup = true
      }),
      title = "Page 0",
      name = "Page0"
    },
    {
      Gtk.Label({
        visible = true,
        label = "<span size='xx-large' font_weight='bold'>Page 1</span>",
        use_markup = true
      }),
      title = "Page 1",
      name = "Page1"
    },
    {
      Gtk.Label({
        visible = true,
        label = "<span size='xx-large' font_weight='bold'>Page 2</span>",
        use_markup = true
      }),
      title = "Page 2",
      name = "Page2"
    },
    {
      Gtk.Label({
        visible = true,
        label = "<span size='xx-large' font_weight='bold'>Page 3</span>",
        use_markup = true
      }),
      title = "Page 3",
      name = "Page3"
    }
  })

  local box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.HORIZONTAL,

    Gtk.StackSidebar({
      visible = true,
      stack = stack,
      halign = Gtk.Align.CENTER
    }),
    {
      stack,
      expand = true
    }
  })

  window:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)