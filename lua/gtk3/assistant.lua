local lgi = require("lgi")
local Gtk = lgi.require("Gtk", "3.0")
local Glib = lgi.require("GLib")

-- GtkAssistant: a widget for guiding the user through step to achieve something

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.Assistant"
local appTitle = "GtkAssistant"
local appWelcomeText = "<span font='Bold 16'>Welcome to the GtkAssistant example</span>"
local app = Gtk.Application { application_id = appID }

local function doPage2(assistantWindow)
  local grid = Gtk.Grid()
  local infoLabel = Gtk.Label.new("Fill this form")
  local nameLabel = Gtk.Label.new("Full name")
  local usernameLabel = Gtk.Label.new("Username")
  local passwordLabel = Gtk.Label.new("Password")
  local nameEntry = Gtk.Entry()
  local usernameEntry = Gtk.Entry()
  local passwordEntry = Gtk.Entry { visibility = false, input_purpose = Gtk.InputPurpose.PASSWORD }
  local doneButton = Gtk.Button.new_with_label("Done")

  grid.column_spacing = 10
  grid.row_spacing = 10
  grid.halign = Gtk.Align.CENTER
  grid.valign = Gtk.Align.CENTER
  grid:attach(infoLabel, 0, 0, 2, 1)
  grid:attach(nameLabel, 0, 1, 1, 1)
  grid:attach(nameEntry, 1, 1, 1, 1)
  grid:attach(usernameLabel, 0, 2, 1, 1)
  grid:attach(usernameEntry, 1, 2, 1, 1)
  grid:attach(passwordLabel, 0, 3, 1, 1)
  grid:attach(passwordEntry, 1, 3, 1, 1)
  grid:attach(doneButton, 1, 4, 1, 1)
  grid:show_all()

  function doneButton:on_clicked()
    assistantWindow:set_page_complete(grid, true)
  end

  return grid
end

local function doPage3(assistantWindow)
  local progressBar = Gtk.ProgressBar()
  local box = Gtk.Box.new(Gtk.Orientation.VERTICAL, 10)

  box.halign = Gtk.Align.CENTER
  box.valign = Gtk.Align.CENTER
  box:pack_start(Gtk.Label.new("Installing the system..."), false, false, 0)
  box:pack_start(progressBar, false, false, 0)
  box:show_all()

  progressBar.width_request = 240
  progressBar.pulse_step = 0.2

  function assistantWindow:on_apply()
    Glib.timeout_add(200, 200, function ()
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

function app:on_activate()
  self.active_window:present()
end

function app:on_startup()
  local window = Gtk.Assistant()
  local headerBar = Gtk.HeaderBar()
  local page1 = Gtk.Label { visible = true, label = appWelcomeText, use_markup = true }
  local page2 = doPage2(window)
  local page3 = doPage3(window)
  local page4 = Gtk.Label { visible = true, label = "System installed successfully!" }

  self:add_window(window)

  window:set_titlebar(headerBar)
  window:set_default_size(800, 400)
  window.on_cancel = Gtk.Widget.destroy
  window.on_close = Gtk.Widget.destroy

  window:append_page(page1)
  window:append_page(page2)
  window:append_page(page3)
  window:append_page(page4)

  window:set_page_title(page1, "Welcome")
  window:set_page_title(page2, "Create account")
  window:set_page_title(page3, "Installing system")
  window:set_page_title(page4, "Summary")

  window:set_page_type(page1, 1)
  window:set_page_type(page2, 2)
  window:set_page_type(page3, 4)
  window:set_page_type(page4, 3)

  window:set_page_complete(page1, true)

  headerBar.visible = true
  headerBar.subtitle = appTitle
  headerBar.show_close_button = true
end

return app:run(arg)