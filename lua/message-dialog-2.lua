lgi = require "lgi"
Gtk = lgi.require "Gtk"

dialog = Gtk.MessageDialog { text = "This is a text message.", buttons = "YES_NO" }

-- https://docs.gtk.org/gtk3/method.Dialog.response.html
function dialog:on_response(response_id)
  --print("response_id:",response_id)

  -- https://valadoc.org/gtk+-3.0/Gtk.ResponseType.html
  if response_id==Gtk.ResponseType.YES then print("yes")
  elseif response_id==Gtk.ResponseType.NO then print("no")
  elseif response_id==Gtk.ResponseType.DELETE_EVENT then print("delete-event")
  end

  Gtk.main_quit()
end

dialog:show_all()
Gtk.main()
