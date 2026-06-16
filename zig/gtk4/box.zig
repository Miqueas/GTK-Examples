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
    var box = gtk.Box.new(.vertical, 10);
    var hint_text = gtk.Label.new("Click the button");
    var button = gtk.Button.newWithLabel("🤔");

    window.as(gtk.Window).setTitle(APP_TITLE);
    window.as(gtk.Window).setChild(box.as(gtk.Widget));
    window.as(gtk.Window).setDefaultSize(400, 400);

    box.append(hint_text.as(gtk.Widget));
    box.append(button.as(gtk.Widget));
    box.as(gtk.Widget).setHalign(.center);
    box.as(gtk.Widget).setValign(.center);

    button.as(gtk.Widget).setHalign(.center);
    button.as(gtk.Widget).setValign(.center);
    _ = gtk.Button.signals.clicked.connect(button, ?*anyopaque, &onClicked, null, .{});
}

var count: i32 = 0;

fn onClicked(_: *gtk.Button, _: ?*anyopaque) callconv(.c) void {
    count += 1;
    std.debug.print("You clicked {} times!\n", .{ count });
}