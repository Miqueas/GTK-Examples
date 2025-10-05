const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AboutDialog";
const string APP_TITLE = "Gtk.AboutDialog";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var app = self as Gtk.Application;
  var window = app?.get_active_window() as Gtk.AboutDialog?;
  window?.run();
  window?.destroy();
}

void on_app_startup(Application self) {
  var dialog = new Gtk.AboutDialog();

  dialog.modal = true;
  dialog.artists = { "Josué Martínez" };
  dialog.authors = { "Josué Martínez" };
  dialog.documenters = { "Josué Martínez" };
  dialog.translator_credits = "Josué Martínez";
  dialog.program_name = APP_TITLE;
  dialog.comments = "GTK+ 3.0 AboutDialog Example";
  dialog.copyright = "Copyright © 2021-2025 Josué Martínez";
  dialog.version = "0.1.0";
  dialog.license = "Copyright (C) 2021-2025 Josué Martínez

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
  3. This notice may not be removed or altered from any source distribution.";
  dialog.wrap_license = true;
  dialog.website = "https://github.com/Miqueas/GTK-Examples";
  dialog.website_label = "GitHub Repository";
  dialog.application = self as Gtk.Application;
}