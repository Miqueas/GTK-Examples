local lgi   = require("lgi")
local Gtk   = lgi.require("Gtk", "3.0")
local Pango = lgi.require("Pango", "1.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Dialog1"
})

function App:on_startup()
  --[[ GtkDialog:

    A (generic) popup window

  ]]
  local Dialog = Gtk.Dialog({
    application = self,
    default_width = 400,
    border_width = 10,
    title = "GtkDialog - Example 1"
  })

  Dialog:add_button("Yes 👍", Gtk.ResponseType.OK)
  Dialog:add_button("No 🛑", Gtk.ResponseType.CANCEL)

  local TitleText = [[<span size="x-large" font-weight="bold">Universe destruction</span>]]
  local Title = Gtk.Label({ visible = true, label = TitleText, use_markup = true })

  local SummaryText = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands."
  local Summary = Gtk.Label({
    visible = true,
    label = SummaryText,
    xalign = 0,
    wrap = true,
    wrap_mode = Pango.WrapMode.CHAR
  })

  local EpilogText = [[<span size="large" font-weight="bold">Do you accept?</span>]]
  local Epilog = Gtk.Label({ visible = true, label = EpilogText, use_markup = true })

  local Content = Dialog:get_content_area()
  Content.spacing = 10
  Content:pack_start(Title, false, true, 0)
  Content:pack_start(Summary, false, true, 0)
  Content:pack_start(Epilog, false, true, 10)

  self:add_window(Dialog)
end

function App:on_activate()
  -- When you work with dialogs, use this instead of 'present()'
  local Response = self.active_window:run()

  if Response == Gtk.ResponseType.OK then
    self.active_window:destroy()
    print("Universe destroyed! 💥")
  elseif Response == Gtk.ResponseType.CANCEL then
    self.active_window:destroy()
    print("Universe is in peace now! 🙏")
  else
    self.active_window:destroy()
    print("Nothing happens! 🤔")
  end
end

return App:run(arg)