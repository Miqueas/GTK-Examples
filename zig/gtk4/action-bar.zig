const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk4.ActionBar";
const APP_TITLE = "GtkActionBar";

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
    var window = gtk.ApplicationWindow.new(app);
    var action_bar = gtk.ActionBar.new();
    var action_bar_label = gtk.Label.new("Something");
    var action_bar_button = gtk.Button.newWithLabel("A button");
    var box = gtk.Box.new(.vertical, 0);
    var box_label = gtk.Label.new("App content");

    gtk.Window.setTitle(window.as(gtk.Window), APP_TITLE);
    gtk.Window.setChild(window.as(gtk.Window), box.as(gtk.Widget));
    gtk.Window.setDefaultSize(window.as(gtk.Window), 400, 400);

    action_bar.packStart(action_bar_label.as(gtk.Widget));
    action_bar.packEnd(action_bar_button.as(gtk.Widget));

    box.append(box_label.as(gtk.Widget));
    box.append(action_bar.as(gtk.Widget));
}