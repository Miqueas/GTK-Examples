const std = @import("std");
const gtk = @import("gtk4");
const gio = @import("gio");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.ApplicationWindow";
const APP_TITLE = "GtkApplicationWindow";

pub fn main(init: std.process.Init) void {
    var app = gtk.Application.new(APP_ID, .{});
    defer app.unref();

    _ = gio.Application.signals.startup.connect(app, ?*anyopaque, &onStartup, null, .{});
    _ = gio.Application.signals.activate.connect(app, ?*anyopaque, &onActivate, null, .{});

    const argv = init.minimal.args.vector;
    const status = app.as(gio.Application).run(
        @intCast(argv.len),
        @ptrCast(@constCast(argv.ptr))
    );

    std.process.exit(@intCast(status));
}

fn onActivate(app: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    if (app.getActiveWindow()) |window| window.present();
}

fn onStartup(app: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    var window = gtk.ApplicationWindow.new(app);
    window.as(gtk.Window).setTitle(APP_TITLE);
    window.as(gtk.Window).setDefaultSize(400, 400);
}