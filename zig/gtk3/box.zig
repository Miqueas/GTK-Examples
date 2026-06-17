const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.Box";
const APP_TITLE = "GtkBox";

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

fn onActivate(self: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    if (self.getActiveWindow()) |window| window.present();
}

fn onStartup(self: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    var window = gtk.ApplicationWindow.new(self);
    var label = gtk.Label.new("Click the button");
    var button = gtk.Button.newWithLabel("🤔");
    var box = gtk.Box.new(.vertical, 10);

    gtk.Window.setTitle(window.as(gtk.Window), APP_TITLE);
    gtk.Window.setDefaultSize(window.as(gtk.Window), 400, 400);
    gtk.Container.add(window.as(gtk.Container), box.as(gtk.Widget));

    gtk.Widget.setHalign(button.as(gtk.Widget), .center);
    gtk.Widget.setValign(button.as(gtk.Widget), .center);
    _ = gtk.Button.signals.clicked.connect(button, ?*anyopaque, &onClicked, null, .{});

    gtk.Widget.setHalign(box.as(gtk.Widget), .center);
    gtk.Widget.setValign(box.as(gtk.Widget), .center);
    box.packStart(label.as(gtk.Widget), gtk.@"false"(), gtk.@"true"(), 0);
    box.packStart(button.as(gtk.Widget), gtk.@"false"(), gtk.@"true"(), 0);
    gtk.Widget.showAll(box.as(gtk.Widget));
}

var count: i32 = 0;

fn onClicked(_: *gtk.Button, _: ?*anyopaque) callconv(.c) void {
    count += 1;
    std.debug.print("You clicked {} times!\n", .{ count });
}