local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "4.0")

-- Gtk.ColumnView: A widget to display data in a tabular way

local APP_ID <const> = "io.github.Miqueas.GTK-Examples.Lua.Gtk4.ColumnView"
local APP_TITLE <const> = "Gtk.ColumnView"
local app = Gtk.Application { application_id = APP_ID, flags = 0 }

local function on_factory_setup(self, list_item)
  local label = Gtk.Label {}
  label.halign = Gtk.Align.START
  list_item:set_child(label)
end

function app:on_startup()
  local list_model = Gtk.StringList {}
  local selection_model = Gtk.NoSelection { model = list_model }
  local key_factory = Gtk.SignalListItemFactory {}
  local value_factory = Gtk.SignalListItemFactory {}
  local window = Gtk.ApplicationWindow { application = self }
  local scroll = Gtk.ScrolledWindow {}
  local column_view = Gtk.ColumnView { model = selection_model }
  local key_column = Gtk.ColumnViewColumn { title = "Key", factory = key_factory }
  local value_column = Gtk.ColumnViewColumn { title = "Value", factory = value_factory }

  for i = 0, 255 do list_model:append(tostring(i)) end

  key_factory.on_setup = on_factory_setup
  function key_factory:on_bind(list_item)
    local label = list_item.child
    local item = list_item.item
    label:set_label(("Key: %s"):format(item.string))
  end

  value_factory.on_setup = on_factory_setup
  function value_factory:on_bind(list_item)
    local label = list_item.child
    local item = list_item.item
    label:set_label(("Value: %s"):format(item.string))
  end

  window.child = scroll
  window.title = APP_TITLE
  window:set_default_size(400, 400)

  scroll.child = column_view

  column_view.reorderable = false
  column_view.show_row_separators = true
  column_view.show_column_separators = true
  column_view:append_column(key_column)
  column_view:append_column(value_column)

  key_column.expand = true
  value_column.expand = true
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)