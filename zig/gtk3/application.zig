const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.Application";

pub fn main(init: std.process.Init) void {
    const app = gtk.Application.new(APP_ID, .{});
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

fn onActivate(_: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    std.debug.print("Hello there!\n", .{});
}

fn onStartup(_: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    std.debug.print("Initializing app... ", .{});
    std.debug.print("Done!\n", .{});
}