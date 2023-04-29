local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

-- GtkInfoBar: an "in-app notifications" like widget

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.InfoBar"
local appTitle = "GtkInfoBar"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    --border_width = 10
  })

  local box = Gtk.Box({ visible = true, orientation = Gtk.Orientation.VERTICAL })
  local infoButton = Gtk.Button({ visible = true, label = "Info" })
  local warningButton = Gtk.Button({ visible = true, label = "Warning" })
  local questionButton = Gtk.Button({ visible = true, label = "Question" })
  local errorButton = Gtk.Button({ visible = true, label = "Error" })
  local otherButton = Gtk.Button({ visible = true, label = "Other" })

  local function createInfoBar(self, data)
    local infoBar = Gtk.InfoBar({
      visible = true,
      message_type = Gtk.MessageType[self.label:upper()],
      show_close_button = true
    })

    -- For this widget, the 'get_content_area()' method always returns a Gtk.Box
    infoBar
      :get_content_area()
      :pack_start(Gtk.Label({ visible = true, label = self.label }), false, true, 0)

    -- When an action widget is clicked, this signal is emitted
    function infoBar:on_response()
      -- For this case, just remove it from the Gtk.Box and then destroy it
      box:remove(self)
      self:destroy()
    end

    -- Add the info bar to the Gtk.Box
    box:pack_start(infoBar, false, true, 0)
  end

  infoButton.on_clicked = createInfoBar
  warningButton.on_clicked = createInfoBar
  questionButton.on_clicked = createInfoBar
  errorButton.on_clicked = createInfoBar
  otherButton.on_clicked = createInfoBar

  local grid = Gtk.Grid({
    visible = true,
    column_homogeneous = true,
    row_homogeneous = true,
    column_spacing = 10,
    row_spacing = 10,

    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    { infoButton, top_attach = 0, left_attach = 0 },
    { warningButton, top_attach = 0, left_attach = 1 },
    { questionButton, top_attach = 1, left_attach = 0 },
    { errorButton, top_attach = 1, left_attach = 1 },
    { otherButton, top_attach = 2, left_attach = 0, width = 2 },
  })

  box:pack_end(grid, true, true, 0)
  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)