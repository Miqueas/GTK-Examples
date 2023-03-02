local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkFileChooserDialog"
})

function App:on_startup()
  --[[ GtkFileChooserDialog:

    A file selection dialog

  ]]
  local Dialog  = Gtk.FileChooserDialog({
    title = "Select a file",
    action = Gtk.FileChooserAction.OPEN
  })

  Dialog:add_button("Open", Gtk.ResponseType.OK)
  Dialog:add_button("Cancel", Gtk.ResponseType.CANCEL)

  self:add_window(Dialog)
end

function App:on_activate()
  local Res = self.active_window:run()

  if Res == Gtk.ResponseType.OK then
    local name = self.active_window:get_filename()
    self.active_window:destroy()
    print("You selected: " .. name)
  elseif Res == Gtk.ResponseType.CANCEL then
    self.active_window:destroy()
    print("Canceled")
  else
    self.active_window:destroy()
    print("Something else")
  end
end

return App:run()