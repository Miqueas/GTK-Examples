local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.InfoBar"
})

function App:on_startup()
  Gtk.ApplicationWindow({
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })
end

function App:on_activate()
  self.active_window:set_titlebar(Gtk.HeaderBar({
    visible = true,
    show_close_button = true,
    title = "GtkInfoBar"
  }))

  local Box         = Gtk.Box({ visible = true, orientation = Gtk.Orientation.VERTICAL })
  local InfoBtn     = Gtk.Button({ visible = true, label = "Info" })
  local WarningBtn  = Gtk.Button({ visible = true, label = "Warning" })
  local QuestionBtn = Gtk.Button({ visible = true, label = "Question" })
  local ErrorBtn    = Gtk.Button({ visible = true, label = "Error" })
  local OtherBtn    = Gtk.Button({ visible = true, label = "Other" })

  function CreateInfoBar(self, data)
    --[[ GtkInfoBar:

      A widget that can be used to show messages to the user.
      Think in it as In-App notifications. The GtkInfoBar API
      is very similar to the GtkDialog API

    ]]
    local InfoBar = Gtk.InfoBar({
      visible = true,
      message_type = Gtk.MessageType[self.label:upper()],
      show_close_button = true
    })

    -- For this widget, the 'get_content_area()' method always returns a Gtk.Box
    InfoBar
      :get_content_area()
      :pack_start(Gtk.Label({ visible = true, label = self.label }), false, true, 0)

    -- When an action widget is clicked, this signal is emitted
    function InfoBar:on_response()
      -- For this case, just remove it from the Gtk.Box and then destroy it
      Box:remove(self)
      self:destroy()
    end

    -- Add the info bar to the Gtk.Box
    Box:pack_start(InfoBar, false, true, 0)
  end

  InfoBtn.on_clicked     = CreateInfoBar
  WarningBtn.on_clicked  = CreateInfoBar
  QuestionBtn.on_clicked = CreateInfoBar
  ErrorBtn.on_clicked    = CreateInfoBar
  OtherBtn.on_clicked    = CreateInfoBar

  local Grid = Gtk.Grid({
    visible = true,
    column_homogeneous = true,
    row_homogeneous = true,
    column_spacing = 10,
    row_spacing = 10,

    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    { InfoBtn,     top_attach = 0, left_attach = 0 },
    { WarningBtn,  top_attach = 0, left_attach = 1 },
    { QuestionBtn, top_attach = 1, left_attach = 0 },
    { ErrorBtn,    top_attach = 1, left_attach = 1 },
    { OtherBtn,    top_attach = 2, left_attach = 0, width = 2 },
  })

  Box:pack_end(Grid, true, true, 0)

  self.active_window:add(Box)
  self.active_window:present()
end

return App:run(arg)