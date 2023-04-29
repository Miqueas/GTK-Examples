local lgi   = require("lgi")
local Gtk   = lgi.require("Gtk", "3.0")

-- GtkMessageDialog: a basic GtkDialog for messages

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.MessageDialog1"
local appTitle = "GtkMessageDialog"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local titleMarkup = [[<span size="x-large" font-weight="bold">Universe destruction</span>]]
  local messageText = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands."

  local messageDialog = Gtk.MessageDialog({
    application = self,
    buttons = Gtk.ButtonsType.NONE,
    message_type = Gtk.MessageType.QUESTION,
    title = appTitle,
    text = titleMarkup,
    use_markup = true,
    secondary_text = messageText
  })

  messageDialog:add_button("Yes 👍", Gtk.ResponseType.OK)
  messageDialog:add_button("No 🛑", Gtk.ResponseType.CANCEL)
end

function app:on_activate()
  -- When you work with dialogs, use this instead of 'present()'
  local response = self.active_window:run()

  if response == Gtk.ResponseType.OK then
    print("Universe destroyed! 💥")
  elseif response == Gtk.ResponseType.CANCEL then
    print("Universe is in peace now! 🙏")
  else
    print("Nothing happens! 🤔")
  end

  self.active_window:destroy()
end

return app:run(arg)