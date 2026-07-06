const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const gobject = @import("gobject");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.AppChooserDialog";
const APP_TITLE = "GtkAppChooserDialog";

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
    if (app.getActiveWindow() == null) return;

    const window = app.getActiveWindow().?;
    const dialog = gobject.ext.cast(gtk.Dialog, window).?;
    const result = dialog.run();

    switch (@as(gtk.ResponseType, @enumFromInt(result))) {
        .ok => {
            const app_chooser = gobject.ext.cast(gtk.AppChooser, window).?;
            const info = gtk.AppChooser.getAppInfo(app_chooser).?;
            std.debug.print("ID: {s}\n", .{ info.getId().? });
            std.debug.print("Executable: {s}\n", .{ info.getExecutable() });
            std.debug.print("Description: {s}\n", .{ info.getDescription().? });
            std.debug.print("Commandline: {s}\n", .{ info.getCommandline().? });
            std.debug.print("Display name: {s}\n", .{ info.getDisplayName() });
        },
        else => {},
    }

    gtk.Widget.destroy(window.as(gtk.Widget));
}

fn onStartup(app: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    const dialog = gtk.AppChooserDialog.newForContentType(null, .{}, "image/png");

    gtk.Window.setTitle(dialog.as(gtk.Window), APP_TITLE);
    gtk.Window.setApplication(dialog.as(gtk.Window), app);
    gtk.Container.setBorderWidth(dialog.as(gtk.Container), 10);
}