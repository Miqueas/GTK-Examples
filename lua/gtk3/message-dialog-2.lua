local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.MessageDialog2"
local appTitle = "GtkMessageDialog"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local titleMarkup = [[<span size="x-large" font-weight="bold">Universe destruction</span>]]
  local messageText = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands."

  local messageDialog = Gtk.MessageDialog({
    title = appTitle,
    application = self,
    buttons = Gtk.ButtonsType.YES_NO,
    message_type = Gtk.MessageType.QUESTION,
    text = titleMarkup,
    secondary_text = messageText,
    use_markup = true
  })

  function messageDialog:on_response(responseID)
    if responseID == Gtk.ResponseType.YES then
      print("Universe destroyed! 💥")
    elseif responseID == Gtk.ResponseType.NO then
      print("Universe is in peace now! 🙏")
    else
      print("Something else...")
      print("Response ID: " .. tostring(responseID))
    end

    self:destroy()
  end
end

function app:on_activate()
  self.active_window:run()
end

return app:run(arg)