const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AboutDialog";
const string appTitle = "GtkAboutDialog";
const string[] artists = { "Josué Martínez" };
const string[] authors = { "Josué Martínez" };
const string[] documenters = { "Josué Martínez" };

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();

  Gtk.show_about_dialog(window,
    modal: true,
    artists: artists,
    authors: authors,
    documenters: documenters,
    translator_credits: "Josué Martínez",
    program_name: appTitle,
    comments: "GTK+ 3.0 AboutDialog Example",
    copyright: "Copyright © 2021-2025 Josué Martínez",
    version: "0.1.0",
    license: "Copyright (C) 2021-2025 Josué Martínez
    
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
    3. This notice may not be removed or altered from any source distribution.",
    wrap_license: true,
    website: "https://github.com/Miqueas/GTK-Examples",
    website_label: "GitHub Repository",
    destroy_with_parent: true
  );
}

void onAppStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var label = new Gtk.Label("Just an empty window") { visible = true };

  with (window) {
    add(label);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }
}