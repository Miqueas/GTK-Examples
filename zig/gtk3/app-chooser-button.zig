const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.AppChooserButton";
const APP_TITLE = "GtkAppChooserButton";

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
    const window = gtk.ApplicationWindow.new(app);
    const app_chooser_button = gtk.AppChooserButton.new("image/png");

    gtk.Window.setTitle(window.as(gtk.Window), APP_TITLE);
    gtk.Window.setDefaultSize(window.as(gtk.Window), 400, 400);
    gtk.Container.add(window.as(gtk.Container), app_chooser_button.as(gtk.Widget));
    gtk.Container.setBorderWidth(window.as(gtk.Container), 10);

    gtk.Widget.setVisible(app_chooser_button.as(gtk.Widget), 1);
    gtk.Widget.setHalign(app_chooser_button.as(gtk.Widget), .center);
    gtk.Widget.setValign(app_chooser_button.as(gtk.Widget), .center);
}