import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.AboutDialog"
appTitle = "GtkAboutDialog"
app = Gtk.Application(application_id = appID)

def onAppActivate(self):
  window = self.get_active_window()
  window.present()

def onAppStartup(self):
  dialog = Gtk.AboutDialog()
  dialog.set_modal(True)
  dialog.set_artists([ "Josué Martínez" ])
  dialog.set_authors([ "Josué Martínez" ])
  dialog.set_documenters([ "Josué Martínez" ])
  dialog.set_translator_credits("Josué Martínez")
  dialog.set_program_name(appTitle)
  dialog.set_comments("GTK+ 3.0 AboutDialog Example")
  dialog.set_copyright("Copyright © 2021-2025 Josué Martínez")
  dialog.set_version("0.1.0")
  dialog.set_license("""Copyright (C) 2021-2025 Josué Martínez

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.""")
  dialog.set_wrap_license(True)
  dialog.set_website("https://github.com/Miqueas/GTK-Examples")
  dialog.set_website_label("GitHub Repository")
  dialog.set_application(self)

app.connect("activate", onAppActivate)
app.connect("startup", onAppStartup)

sys.exit(app.run(sys.argv))