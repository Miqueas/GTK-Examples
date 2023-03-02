local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local app = Gtk.Application { application_id = "com.github.Miqueas.Lua-GTK3-Examples.GtkFlowBox" }

function app:on_activate()
  self.active_window:present()
end

function app:on_startup()
  local win = Gtk.ApplicationWindow {
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  }

  win:set_titlebar(Gtk.HeaderBar {
    visible = true,
    show_close_button = true,
    title = "GtkFlowBox"
  })

  local flowbox = Gtk.FlowBox {
    visible = true,
    valign = Gtk.Align.START,
    selection_mode = Gtk.SelectionMode.NONE,
    max_children_per_line = 30
  }

  local scroll = Gtk.ScrolledWindow {
    visible = true,
    hscrollbar_policy = Gtk.PolicyType.NEVER
  }

  local icons = {
    "face-angry",
    "face-surprise",
    "face-laugh",
    "face-plain",
    "face-sad",
    "face-cool",
    "face-smirk",
    "face-sick",
    "face-kiss",
    "face-smile"
  }

  math.randomseed(os.time())

  for i = 0, 399 do
    flowbox:insert(Gtk.Image {
      visible = true,
      icon_name = icons[math.random(1, 10)],
      pixel_size = 32
    }, i)
  end

  scroll:add(flowbox)
  win:add(scroll)
end

return app:run(arg)