const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Application";

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

fn onActivate(_: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    std.debug.print("Hello there!\n", .{});
}

fn onStartup(_: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    std.debug.print("Initializing app... ", .{});
    std.debug.print("Done!\n", .{});
}