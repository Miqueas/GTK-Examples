local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local Gio = lgi.Gio

-- GtkApplication: Provides an application interface

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.Application"
local app = Gtk.Application.new(appID, Gio.ApplicationFlags.FLAGS_NONE)

-- I recommend to check out this links for more information:
-- https://wiki.gnome.org/HowDoI/GtkApplication
-- https://developer.gnome.org/gio/stable/GApplication.html
-- https://developer.gnome.org/gtk3/stable/GtkApplication.html
function app:on_startup()
  -- The ::startup signal is called only once, so it's recommended to create/prepare
  -- all the GUI here and then present it on the ::activate signal
  print("app::startup called")
end

function app:on_activate()
  -- The ::activate signal can be triggered indefinitely, so please try to not do heavy
  -- things here. Check out the doc links above for more details
  print("app::activate called")
end

return app:run(arg)