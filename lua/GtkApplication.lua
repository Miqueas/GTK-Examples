local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

--[[ GtkApplication:

  Provides an application interface. I recommend you to read the
  info in the links below.

]]
local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Application"
})

-- For more info about these signals, see this:
-- https://wiki.gnome.org/HowDoI/GtkApplication
-- https://developer.gnome.org/gio/stable/GApplication.html
-- https://developer.gnome.org/gtk3/stable/GtkApplication.html
function App:on_startup()
  print("Application::startup called")
end

function App:on_activate()
  print("Application::activate called")
end

return App:run(arg)