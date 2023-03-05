local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Stack2"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 600,
    default_height = 400
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkStack",
    subtitle = "Example 2"
  }))

  --[[ GtkStack:

    A container that shows only one (1) child at a time

  ]]
  local Stack = Gtk.Stack({
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

  local Box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.HORIZONTAL,

    Gtk.StackSidebar({
      visible = true,
      stack = Stack,
      halign = Gtk.Align.CENTER
    }),
    {
      Stack,
      expand = true
    }
  })

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)