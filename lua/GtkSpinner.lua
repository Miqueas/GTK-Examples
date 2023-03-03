local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local app = Gtk.Application { application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Spinner" }

function app:on_activate()
  self.active_window:present()
end

function app:on_startup()
  local win = Gtk.ApplicationWindow {
    application = self,
    default_width = 300,
    default_height = 300,
    border_width = 10
  }

  win:set_titlebar(Gtk.HeaderBar {
    visible = true,
    show_close_button = true,
    title = "GtkSpinner"
  })

  local spinner = Gtk.Spinner { visible = true }
  local btn = Gtk.Button { visible = true, label = "Start" }

  local box = Gtk.Box {
    visible = true,
    spacing = 10,
    orientation = Gtk.Orientation.VERTICAL,
    valign = Gtk.Align.CENTER,
    halign = Gtk.Align.CENTER,

    spinner,
    btn
  }

  function btn:on_clicked()
    if spinner.active then
      self.label = "Start"
      spinner:stop()
    else
      self.label = "Stop"
      spinner:start()
    end
  end

  win:add(box)
end

return app:run(arg)