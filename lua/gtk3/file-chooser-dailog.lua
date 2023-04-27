local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkFileChooserDialog: a file selection dialog

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.FileChooserDialog"
local appTitle = "GtkFileChooserDialog"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local fileChooserDialog  = Gtk.FileChooserDialog({
    title = appTitle,
    application = self,
    action = Gtk.FileChooserAction.OPEN
  })

  fileChooserDialog:add_button("Open", Gtk.ResponseType.OK)
  fileChooserDialog:add_button("Cancel", Gtk.ResponseType.CANCEL)
end

function app:on_activate()
  local response = self.active_window:run()

  if response == Gtk.ResponseType.OK then
    local name = self.active_window:get_filename()
    print("You selected: " .. name)
  elseif response == Gtk.ResponseType.CANCEL then
    print("Canceled")
  else
    print("Something else")
  end

  self.active_window:destroy()
end

return app:run()