local lgi   = require("lgi")
local Gtk   = lgi.require("Gtk", "3.0")
local Pango = lgi.require("Pango", "1.0")

-- GtkDialog: A generic popup window

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Dialog2"
local appTitle = "GtkDialog"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local dialog = Gtk.Dialog({
    application = self,
    use_header_bar = 1,
    default_width = 400,
    border_width = 10
  })

  dialog:add_button("Yes 😈👍", Gtk.ResponseType.OK)
  dialog:add_button("No 💀🛑", Gtk.ResponseType.CANCEL)
  dialog:get_header_bar().title = appTitle

  local titleText = [[<span size="x-large" font-weight="bold">Universe destruction</span>]]
  local titleLabel = Gtk.Label({ visible = true, label = titleText, use_markup = true })

  local summaryText = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands."
  local summaryLabel = Gtk.Label({
    visible = true,
    label = summaryText,
    xalign = 0,
    wrap = true,
    wrap_mode = Pango.WrapMode.CHAR
  })

  local epilogText = [[<span size="large" font-weight="bold">Do you accept?</span>]]
  local epilogLabel = Gtk.Label({ visible = true, label = epilogText, use_markup = true })

  local contentBox = dialog:get_content_area()
  contentBox.spacing = 10
  contentBox:pack_start(titleLabel, false, true, 0)
  contentBox:pack_start(summaryLabel, false, true, 0)
  contentBox:pack_start(epilogLabel, false, true, 10)
end

function app:on_activate()
  -- When you work with dialogs, use this instead of 'present()'
  local response = self.active_window:run()

  if response == Gtk.ResponseType.OK then
    self.active_window:destroy()
    print("Universe destroyed! 💥")
  elseif response == Gtk.ResponseType.CANCEL then
    self.active_window:destroy()
    print("Universe is in peace now! 🙏")
  else
    self.active_window:destroy()
    print("Nothing happens! 🤔")
  end
end

return app:run(arg)