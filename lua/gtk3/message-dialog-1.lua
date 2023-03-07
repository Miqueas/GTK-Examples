local lgi   = require("lgi")
local Gtk   = lgi.require("Gtk", "3.0")
local Pango = lgi.require("Pango", "1.0")

local App = Gtk.Application({
  application_id = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.MessageDialog"
})

function App:on_startup()
  local Title   = [[<span size="x-large" font-weight="bold">Universe destruction</span>]]
  local Message = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands."

  --[[ GtkMessageDialog:

    A GtkDialog for basic popup windows with a predefined design: title, message and choice buttons.
    Useful if you don't want to make a complex dialog.

  ]]
  local Dialog = Gtk.MessageDialog({
    application = self,
    buttons = Gtk.ButtonsType.NONE,
    message_type = Gtk.MessageType.QUESTION,
    title = "GtkMessageDialog",
    text = Title,
    use_markup = true,
    secondary_text = Message
  })

  Dialog:add_button("Yes 👍", Gtk.ResponseType.OK)
  Dialog:add_button("No 🛑", Gtk.ResponseType.CANCEL)
end

function App:on_activate()
  -- When you work with dialogs, use this instead of 'present()'
  local Res = self.active_window:run()

  if Res == Gtk.ResponseType.OK then
    self.active_window:destroy()
    print("Universe destroyed! 💥")
  elseif Res == Gtk.ResponseType.CANCEL then
    self.active_window:destroy()
    print("Universe is in peace now! 🙏")
  else
    self.active_window:destroy()
    print("Nothing happens! 🤔")
  end
end

return App:run(arg)