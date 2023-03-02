local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

--[[ GtkBuilder:

  A mechanism provided by Gtk that allows build user interfaces
  using a XML definition. That XML definition can be in a file
  or an string of the programming language that you use.

  This can be very helpful, because you don't need create the
  entire UI from code, instead, you can use a XML definition
  of your app UI and in the code side, you write the whatever
  your app will do.

]]
local Builder = Gtk.Builder.new_from_file("GtkBuilder.ui")

local App     = Gtk.Application({
  application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkBuilder1"
})

function App:on_startup()
  self:add_window(Builder:get_object("Window"))
end

function App:on_activate()
  self.active_window:present()
end

return App:run(arg)