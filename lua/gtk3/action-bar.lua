local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkActionBar: A full width container to add contextual actions

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ActionBar"
local appTitle = "GtkActionBar"

local function onAppStartup(self)
  local window = Gtk.ApplicationWindow { application = self, title = appTitle }
  local actionBar = Gtk.ActionBar()
  local box = Gtk.Box { orientation = Gtk.Orientation.VERTICAL }

  window:add(box)
  window:set_default_size(400, 400)

  actionBar:pack_start(Gtk.Label { label = "Something" })
  actionBar:pack_end(Gtk.Button { label = "A button" })

  box:pack_start(Gtk.Label { label = "App content here"}, true, true, 0)
  box:pack_end(actionBar, false, false, 0)
  box:show_all()
end

local app = Gtk.Application { application_id = appID }
app.on_activate = function (self) self.active_window:present() end
app.on_startup = onAppStartup

os.exit(app:run(arg), true)