local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local GObject = lgi.require("GObject")

local Column = { NAME = 1, SELECTED = 2 }

local items = {
  { group = "Code Editors",
    child = {
      { app = "VS Code", selected =  true },
      { app = "Sublime Text", selected = false },
      { app = "Atom", selected = false },
    }
  },
  { group = "Music Services",
    child = {
      { app = "YouTube Music", selected = true },
      { app = "Deezer", selected = true },
      { app = "Spotify", selected = false },
    }
  },
  { group = "Web Browsers",
    child = {
      { app = "Microsoft Edge", selected = true },
      { app = "Google Chrome", selected = true },
      { app = "Mozilla Firefox", selected = false },
    }
  },
}

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.TreeView"
local appTitle = "GtkTreeView"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local window = Gtk.ApplicationWindow.new(self)
  local box = Gtk.Box({ orientation = Gtk.Orientation.VERTICAL, spacing = 10 })
  local titleText = Gtk.Label({ label = "Software Selection" })
  local treeView = Gtk.TreeView()
  local treeViewModel = Gtk.TreeStore.new({ GObject.Type.STRING, GObject.Type.BOOLEAN })

  window:add(box)
  window.title = appTitle
  window.border_width = 10
  window:set_default_size(400, 400)

  box:pack_start(titleText, false, false, 0)
  box:pack_start(treeView, true, true, 0)
  box:show_all()

  treeView.model = treeViewModel
  treeView:append_column(Gtk.TreeViewColumn({ title = "App", expand = true,
    { Gtk.CellRendererText(), { text = Column.NAME } }
  }))

  treeView:append_column(Gtk.TreeViewColumn({ title = "Install",
    { Gtk.CellRendererToggle({ on_toggled = function (self, pathStr)
      print("TODO")
    end }), { active = Column.SELECTED } }
  }))

  for _, item in ipairs(items) do
    local parentIter = treeViewModel:append()
    treeViewModel[parentIter] = {
      [Column.NAME] = item.group,
    }

    for _, child in ipairs(item.child) do
      local childIter = treeViewModel:append(parentIter)
      treeViewModel[childIter] = {
        [Column.NAME] = child.app,
        [Column.SELECTED] = child.selected,
      }
    end
  end
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)