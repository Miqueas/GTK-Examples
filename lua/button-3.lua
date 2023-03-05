local lgi = require"lgi"
local Gtk = lgi.require("Gtk", "3.0")

local Builder = Gtk.Builder.new_from_file("GtkBuilder-02.ui")
local UI      = Builder.objects

local App = Gtk.Application{
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Button3"
}

function App:on_startup()
  self:add_window(UI.Window)
end

function grid_click(button)
  local counter = 1
  function button:on_clicked()
    local label_parent = self.child[1] or self
    label_parent.label = counter
    counter = counter + 1
  end
end

function App:on_activate()
  local window = self.active_window
  for row=1,3 do
    for col=1,3 do
      local name="button"..row..col
      grid_click(UI[name])
    end
  end
  window:present()
end

return App:run(arg)