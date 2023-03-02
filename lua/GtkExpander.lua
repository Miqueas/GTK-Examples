local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkExpander"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    border_width = 10,
    resizable = false
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "Your app title",
    subtitle = "Your app subtitle"
  }))

  local LoremIpsum = [[Duis in metus eros. Duis faucibus rutrum eros eu vestibulum.
Proin et arcu nulla. Etiam at lacinia nibh. Vivamus pellentesque nunc nibh,
ac dignissim massa lobortis ut. Integer eu felis in elit semper ullamcorper
at in ipsum. Suspendisse tempus massa vel nibh tristique vestibulum.
Vestibulum varius eu nunc eu interdum. Curabitur pulvinar velit in purus
facilisis, et auctor augue consequat. Donec finibus felis ligula, a convallis
justo tristique a.]]

  --[[ GtkExpander:

    A widget that allows hide its child, like a GtkRevealer, but you don't need to
    show/hide the child programmatically and has a small "hint" that there is
    "something" hidden.

  ]]
  local Expand = Gtk.Expander({
    visible = true,
    label = [[  <span size="large" font_weight="bold">Lorem ipsum</span>  ]],
    use_markup = true,
    resize_toplevel = true,

    Gtk.Label({ visible = true, label = LoremIpsum, wrap = true })
  })

  self.active_window:add(Expand)
  self.active_window:present()
end

return App:run(arg)