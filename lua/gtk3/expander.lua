local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkExpander: a "more details" widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Expander"
local appTitle = "GtkExpander"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    border_width = 10,
    resizable = false
  })

  local loremText = [[Duis in metus eros. Duis faucibus rutrum eros eu vestibulum.
Proin et arcu nulla. Etiam at lacinia nibh. Vivamus pellentesque nunc nibh,
ac dignissim massa lobortis ut. Integer eu felis in elit semper ullamcorper
at in ipsum. Suspendisse tempus massa vel nibh tristique vestibulum.
Vestibulum varius eu nunc eu interdum. Curabitur pulvinar velit in purus
facilisis, et auctor augue consequat. Donec finibus felis ligula, a convallis
justo tristique a.]]

  local expander = Gtk.Expander({
    visible = true,
    label = [[  <span size="large" font_weight="bold">Lorem ipsum</span>  ]],
    use_markup = true,
    resize_toplevel = true,

    Gtk.Label({ visible = true, label = loremText, wrap = true })
  })

  win:add(expander)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)