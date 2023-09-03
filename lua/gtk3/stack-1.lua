local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkStack: a container that shows only one child at a time

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Stack1"
local appTitle = "GtkStack"
local app = Gtk.Application({ application_id = appID })
local labelText = "<span size='xx-large' font_weight='bold'>Page %d</span>"
local labelTitle = "Page %d"
local labelName = "page%d"

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 600,
    default_height = 400,
    border_width = 10
  })

  local stack = Gtk.Stack({
    transition_type = Gtk.StackTransitionType.SLIDE_LEFT_RIGHT,
    -- Increment this value to see the animation more slow
    transition_duration = 280
  })

  for i = 1, 3 do
    stack:add_titled(
      Gtk.Label({ use_markup = true, label = labelText:format(i) }),
      labelName:format(i),
      labelTitle:format(i)
    )
  end

  local box = Gtk.Box({
    orientation = Gtk.Orientation.VERTICAL,
    { stack, expand = true },
    Gtk.StackSwitcher({ stack = stack, halign = Gtk.Align.CENTER })
  })

  box:show_all()
  window:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)