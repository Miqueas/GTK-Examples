local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local Glib = lgi.require("GLib")

-- GtkAssistant: a widget for guiding the user through step to achieve something

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Assistant"
local appTitle = "GtkAssistant"
local app = Gtk.Application({ application_id = appID })

local function doPage1()
  return Gtk.Label({
    visible = true,
    label = "<span font='Bold 16'>Welcome to the GtkAssistant example</span>",
    use_markup = true
  })
end

local function doPage2(assistantWindow)
  local grid = Gtk.Grid({
    column_spacing = 10,
    row_spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER
  })

  local infoLabel = Gtk.Label({ label = "Fill this form" })
  local nameLabel = Gtk.Label({ label = "Full name", xalign = 0.0, width_request = 110 })
  local usernameLabel = Gtk.Label({ label = "Username", xalign = 0.0, width_request = 110 })
  local passwordLabel = Gtk.Label({ label = "Password", xalign = 0.0, width_request = 110 })
  local nameEntry = Gtk.Entry()
  local usernameEntry = Gtk.Entry()
  local passwordEntry = Gtk.Entry({ visibility = false, input_purpose = Gtk.InputPurpose.PASSWORD })
  local doneButton = Gtk.Button({ label = "Done" })

  function doneButton:on_clicked()
    assistantWindow:set_page_complete(grid, true)
  end

  grid:attach(infoLabel, 0, 0, 2, 1)
  grid:attach(nameLabel, 0, 1, 1, 1)
  grid:attach(nameEntry, 1, 1, 1, 1)
  grid:attach(usernameLabel, 0, 2, 1, 1)
  grid:attach(usernameEntry, 1, 2, 1, 1)
  grid:attach(passwordLabel, 0, 3, 1, 1)
  grid:attach(passwordEntry, 1, 3, 1, 1)
  grid:attach(doneButton, 1, 4, 1, 1)
  grid:show_all()

  return grid
end

local function doPage3(assistantWindow)
  local progressBar = Gtk.ProgressBar({ visible = true, width_request = 240, pulse_step = 0.1 })
  local box = Gtk.Box({
    visible = true,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,

    Gtk.Label({ visible = true, label = "Installing the system..." }),
    progressBar
  })

  function assistantWindow:on_apply()
    Glib.timeout_add(500, 500, function ()
      local fraction = progressBar:get_fraction()

      if fraction == 1 or fraction == 1.0 then
        assistantWindow:set_page_complete(box, true)
        assistantWindow:commit()
        return false
      elseif fraction < 0 then
        progressBar:pulse()
      else
        progressBar:set_fraction(fraction + 0.1)
      end

      return true
    end, 1000)
  end

  return box
end

local function doPage4()
  return Gtk.Label({ visible = true, label = "System installed successfully!" })
end

function app:on_activate()
  self.active_window:present()
end

function app:on_startup()
  local assistantWindow = Gtk.Assistant({
    title = appTitle,
    application = self,
    default_width = 800,
    default_height = 400,
    on_cancel = function (self) self:destroy() end,
    on_close = function (self) self:destroy() end
  })

  local page1 = doPage1()
  local page2 = doPage2(assistantWindow)
  local page3 = doPage3(assistantWindow)
  local page4 = doPage4()

  assistantWindow:append_page(page1)
  assistantWindow:append_page(page2)
  assistantWindow:append_page(page3)
  assistantWindow:append_page(page4)

  assistantWindow:set_page_title(page1, "Welcome")
  assistantWindow:set_page_title(page2, "Create account")
  assistantWindow:set_page_title(page3, "Installing system")
  assistantWindow:set_page_title(page4, "Summary")

  assistantWindow:set_page_type(page1, 1)
  assistantWindow:set_page_type(page2, 2)
  assistantWindow:set_page_type(page3, 4)
  assistantWindow:set_page_type(page4, 3)

  assistantWindow:set_page_complete(page1, true)
end

return app:run(arg)