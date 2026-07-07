const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const glib = @import("glib");
const gobject = @import("gobject");

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.Subclassing";
const APP_TITLE = "Subclassing";

pub fn main(init: std.process.Init) void {
    const app = App.new();
    defer app.unref();

    const argv = init.minimal.args.vector;
    const status = gio.Application.run(
        app.as(gio.Application),
        @intCast(argv.len),
        @ptrCast(@constCast(argv.ptr))
    );

    std.process.exit(@intCast(status));
}

const App = extern struct {
    parent_instance: Parent,

    pub const Parent = gtk.Application;

    pub const getGObjectType =  gobject.ext.defineClass(App, .{
        .classInit = &Class.init,
        .parent_class = &Class.parent,
    });

    pub fn new() *App {
        return gobject.ext.newInstance(App, .{
            .application_id = APP_ID,
            .flags = gio.ApplicationFlags {},
        });
    }

    pub fn as(self: *App, comptime T: type) *T {
        return gobject.ext.as(T, self);
    }

    fn doActivate(self: *App) callconv(.c) void {
        const app = self.as(gtk.Application);
        if (app.getActiveWindow()) |window| window.present();
    }

    fn doStartup(self: *App) callconv(.c) void {
        gio.Application.virtual_methods.startup.call(Class.parent, self.as(Parent));

        const window = gtk.ApplicationWindow.new(self.as(Parent));
        gtk.Window.setTitle(window.as(gtk.Window), APP_TITLE);
        gtk.Window.setDefaultSize(window.as(gtk.Window), 400, 400);
    }

    pub const Class = extern struct {
        parent_class: Parent.Class,

        var parent: *Parent.Class = undefined;

        pub const Instance = App;

        pub fn as(self: *Class, comptime T: type) *T {
            return gobject.ext.as(T, self);
        }

        fn init(self: *Class) callconv(.c) void {
            gio.Application.virtual_methods.startup.implement(self, &doStartup);
            gio.Application.virtual_methods.activate.implement(self, &doActivate);
        }
    };
};