--[[
 @author    Díaz Urbaneja Víctor Eduardo Diex <victor.vector008@gmail.com>
 @date      28.02.2021 02:26:39 -04
]]

local lgi = require('lgi')
local Gtk = lgi.require('Gtk', '3.0')
local Gdk = lgi.require('Gdk', '3.0')
assert = lgi.assert -- With this function I will confirm if a file (in this case custom.css) exists.

--- I load my css
local Provider = Gtk.CssProvider()

-- Show a message if custom.css does not exist
assert(Provider:load_from_path('styles/GtkCssProvider1.css'), 'ERROR: file.css not found')

--- I add my CSS to the current window
local Screen = Gdk.Display.get_default_screen(Gdk.Display:get_default())
local GTK_STYLE_PROVIDER_PRIORITY_APPLICATION = 600
  Gtk.StyleContext.add_provider_for_screen(
  Screen, Provider,
  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
)

local Window = Gtk.Window {
  title = 'Linking CSS Styles',
  width = 200,
  height = 200,
  window_position = Gtk.WindowPosition.CENTER,
  {
    Gtk.Button {
      halign = Gtk.Align.CENTER,
      valign = Gtk.Align.CENTER,
      label = 'Example of the button with css',
      on_clicked = function (self)
        self:get_style_context():add_class('red')
      end
    }
  },
  on_destroy = function()
    Gtk.main_quit()
	end
}

Window:show_all()
Gtk.main()
