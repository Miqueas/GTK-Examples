local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkHeaderBar"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400
  })
end

function App:on_activate()
  --[[ GtkHeaderBar:

    A container that acts as the title bar of the window.
    This is a CSD (Client Side Decorations), since we are
    setting up our own title bar for our window, rather
    than leaving it up to the WM to decorate it.

    In other examples we talk a little more about CSD using CSS.

  ]]
  self.active_window:set_titlebar(Gtk.HeaderBar({
    -- By default, all GTK widgets are not visibles
    visible = true,
    -- GtkHeaderBar don't sets the window controls buttons by default
    -- this property changes that behavior
    show_close_button = true,
    title = "Your app title",
    subtitle = "Your app subtitle"
  }))

  self.active_window:present()
end

return App:run(arg)