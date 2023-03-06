local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkApplication: Provides an application interface

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Application"
local app = Gtk.Application({ application_id = appID })

-- I recommend to check out this links for more information:
-- https://wiki.gnome.org/HowDoI/GtkApplication
-- https://developer.gnome.org/gio/stable/GApplication.html
-- https://developer.gnome.org/gtk3/stable/GtkApplication.html
function app:on_startup()
  -- The ::startup signal is called only once, so it's recommended to create/prepare
  -- all the GUI here and then present it on the ::activate signal
  print("Application::startup called")
end

function app:on_activate()
  -- The ::activate signal can be triggered indefinitely, so please try to not do heavy
  -- things here. Check out the doc links above for more details
  print("Application::activate called")
end

return app:run(arg)