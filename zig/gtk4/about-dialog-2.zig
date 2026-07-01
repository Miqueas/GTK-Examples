const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const gobject = @import("gobject");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk4.AboutDialog2";
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
    if (app.getActiveWindow()) |window| {
        window.present();
        gtk.showAboutDialog(
            window,
            "modal", @as(c_int, 1),
            "artists", @as([*][*:0]const u8, @ptrCast(@constCast(&ARTISTS))),
            "authors", @as([*][*:0]const u8, @ptrCast(@constCast(&AUTHORS))),
            "documenters", @as([*][*:0]const u8, @ptrCast(@constCast(&DOCUMENTERS))),
            "translator-credits", TRANSLATOR_CREDITS,
            "program-name", APP_TITLE,
            "comments", COMMENTS,
            "copyright", COPYRIGHT,
            "version", VERSION,
            "license", LICENSE,
            "wrap-license", @as(c_int, 1),
            "website", WEBSITE,
            "website-label", WEBSITE_TEXT,
            "destroy-with-parent", @as(c_int, 1),
            // Zig doesn't allow `null` values on variadic functions, so I added this instead
            @as([*:0]const u8, ""),
        );
    }
}

fn onStartup(app: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    var window = gtk.ApplicationWindow.new(app);
    var label = gtk.Label.new("(This is just an empty window)");

    gtk.Window.setTitle(window.as(gtk.Window), APP_TITLE);
    gtk.Window.setChild(window.as(gtk.Window), label.as(gtk.Widget));
    gtk.Window.setDefaultSize(window.as(gtk.Window), 400, 400);
}