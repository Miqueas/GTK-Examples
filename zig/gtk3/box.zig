const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Box";
const APP_TITLE = "GtkBox";

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

fn onActivate(self: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    if (self.getActiveWindow()) |window| window.present();
}

fn onStartup(self: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    var window = gtk.ApplicationWindow.new(self);
    var label = gtk.Label.new("Click the button");
    var button = gtk.Button.newWithLabel("🤔");
    var box = gtk.Box.new(.vertical, 10);

    window.as(gtk.Window).setTitle(APP_TITLE);
    window.as(gtk.Window).setDefaultSize(400, 400);
    window.as(gtk.Container).add(box.as(gtk.Widget));

    button.as(gtk.Widget).setHalign(.center);
    button.as(gtk.Widget).setValign(.center);
    _ = gtk.Button.signals.clicked.connect(button, ?*anyopaque, &onClicked, null, .{});

    box.as(gtk.Widget).setHalign(.center);
    box.as(gtk.Widget).setValign(.center);
    box.packStart(label.as(gtk.Widget), 0, 1, 0);
    box.packStart(button.as(gtk.Widget), 0, 1, 0);
    box.as(gtk.Widget).showAll();
}

var count: i32 = 0;

fn onClicked(_: *gtk.Button, _: ?*anyopaque) callconv(.c) void {
    count += 1;
    std.debug.print("You clicked {} times!\n", .{ count });
}