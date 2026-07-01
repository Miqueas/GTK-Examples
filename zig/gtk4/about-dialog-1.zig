const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const gobject = @import("gobject");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk4.AboutDialog1";
const APP_TITLE = "GtkAboutDialog";
const AUTHORS = [_]?[*:0]const u8{ "Josué Martínez", null };
const ARTISTS = [_]?[*:0]const u8{ "Josué Martínez", null };
const DOCUMENTERS = [_]?[*:0]const u8{ "Josué Martínez", null };
const TRANSLATOR_CREDITS = "Josué Martínez";
const COMMENTS = "GTK 4 AboutDialog Example";
const COPYRIGHT = "Copyright © 2021-2026 Josué Martínez";
const VERSION = "0.1.0";
const WEBSITE = "https://github.com/Miqueas/GTK-Examples";
const WEBSITE_TEXT = "GitHub Repository";
const LICENSE =
\\Copyright (C) 2021-2026 Josué Martínez
\\
\\  This software is provided 'as-is', without any express or implied
\\  warranty.  In no event will the authors be held liable for any damages
\\  arising from the use of this software.
\\
\\  Permission is granted to anyone to use this software for any purpose,
\\  including commercial applications, and to alter it and redistribute it
\\  freely, subject to the following restrictions:
\\
\\  1. The origin of this software must not be misrepresented; you must not
\\     claim that you wrote the original software. If you use this software
\\     in a product, an acknowledgment in the product documentation would be
\\     appreciated but is not required.
\\  2. Altered source versions must be plainly marked as such, and must not be
\\     misrepresented as being the original software.
\\  3. This notice may not be removed or altered from any source distribution.
;

pub fn main(init: std.process.Init) void {
    var app = gtk.Application.new(APP_ID, .{});
    defer app.unref();

    _ = gio.Application.signals.startup.connect(app, ?*anyopaque, &onStartup, null, .{});
    _ = gio.Application.signals.activate.connect(app, ?*anyopaque, &onActivate, null, .{});

    const argv = init.minimal.args.vector;
    const status = gio.Application.run(
        app.as(gio.Application),
        @intCast(argv.len),
        @ptrCast(@constCast(argv.ptr))
    );

    std.process.exit(@intCast(status));
}

fn onActivate(app: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    if (app.getActiveWindow()) |window| window.present();
}

fn onStartup(app: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    var dialog = gtk.AboutDialog.new();

    gtk.Window.setModal(dialog.as(gtk.Window), 1);
    gtk.Window.setApplication(dialog.as(gtk.Window), app);
    dialog.setArtists(@ptrCast(@constCast(&ARTISTS)));
    dialog.setAuthors(@ptrCast(@constCast(&AUTHORS)));
    dialog.setDocumenters(@ptrCast(@constCast(&DOCUMENTERS)));
    dialog.setTranslatorCredits(TRANSLATOR_CREDITS);
    dialog.setProgramName(APP_TITLE);
    dialog.setComments(COMMENTS);
    dialog.setCopyright(COPYRIGHT);
    dialog.setVersion(VERSION);
    dialog.setLicense(LICENSE);
    dialog.setWrapLicense(1);
    dialog.setWebsite(WEBSITE);
    dialog.setWebsiteLabel(WEBSITE_TEXT);
}