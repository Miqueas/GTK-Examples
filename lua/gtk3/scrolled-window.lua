local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkScrolledWindow: A container for scrollable content

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.ScrolledWindow"
local appTitle = "GtkScrolledWindow"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400
  })

  local grid = Gtk.Grid({
    visible = true,
    column_homogeneous = true,
    row_homogeneous = true,
    column_spacing = 10,
    row_spacing = 10,
    halign = Gtk.Align.START,
    valign = Gtk.Align.START
  })

  local scroll = Gtk.ScrolledWindow({
    visible = true,
    -- Removes a shadow that is added by default
    shadow_type = Gtk.ShadowType.NONE,
    -- "Expands" the child width, and makes the child use the real allocated width
    propagate_natural_width = true,
    -- Same, but for height
    propagate_natural_height = true,

    grid
  })

  for top = 1, 100 do
    for left = 1, 100 do
      grid:attach(
        Gtk.Label({ visible = true, label = "Top: "..top..". Left: "..left }),
        left - 1,
        top - 1,
        1, 1
      )
    end
  end

  window:add(scroll)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)