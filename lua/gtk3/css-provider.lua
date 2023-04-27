--[[
  @author  Díaz Urbaneja Víctor Eduardo Diex (https://github.com/diazvictor)
  @date    28.02.2021 02:26:39 -04
]]

local lgi = require('lgi')
local Gtk = lgi.require('Gtk', '3.0')

-- GtkCssProvider: CSS-like styling class for widgets

local appID = "io.github.Miqueas.GTK-Examples.Lua.Gtk3.CssProvider"
local appTitle = "GtkCssProvider"
local app = Gtk.Application({ application_id = appID })

function app:on_startup()
  local win = Gtk.ApplicationWindow({
    title = appTitle,
    application = self,
    default_width = 400,
    default_height = 400,
    border_width = 10
  })

  local provider = Gtk.CssProvider()
  provider:load_from_path("css-provider.css")

  local screen = win:get_screen()
  local styleContext = win:get_style_context()
  styleContext.add_provider_for_screen(screen, provider, 600)

  local label = Gtk.Label({
    visible = true,
    label = "Hi there!"
  })

  local button = Gtk.Button({
    visible = true,
    label = "Toggle label style"
  })

  function button:on_clicked()
    local labelStyleContext = label:get_style_context()

    if labelStyleContext:has_class("color-green") then
      labelStyleContext:remove_class("color-green")
    else
      labelStyleContext:add_class("color-green")
    end
  end

  local box = Gtk.Box({
    visible = true,
    halign = Gtk.Align.CENTER,
    valign = Gtk.Align.CENTER,
    orientation = Gtk.Orientation.VERTICAL,
    spacing = 10
  })

  box:pack_start(label, false, false, 0)
  box:pack_start(button, false, false, 0)

  win:add(box)
end

function app:on_activate()
  self.active_window:present()
end

return app:run(arg)