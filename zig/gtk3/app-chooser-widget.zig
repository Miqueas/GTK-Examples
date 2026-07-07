const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const gobject = @import("gobject");

const AppChooserWidgetSetting = enum {
    show_all,
    show_other,
    show_default,
    show_fallback,
    show_recommended,
};

const ToggleData = struct {
    widgets: *[6]*gtk.Widget,
    setting: AppChooserWidgetSetting,
};

const ShutdownData = struct {
    widgets: *[6]*gtk.Widget,
    toggles_data: [5]*ToggleData,
};

var allocator = std.heap.DebugAllocator(.{ .never_unmap = true, .retain_metadata = true }).init;
const gpa = allocator.allocator();
const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.AppChooserWidget";
const APP_TITLE = "GtkAppChooserWidget";

pub fn main(init: std.process.Init.Minimal) void {
    const app = gtk.Application.new(APP_ID, .{});
    defer app.unref();

    _ = gio.Application.signals.startup.connect(app, ?*anyopaque, &onStartup, null, .{});
    _ = gio.Application.signals.activate.connect(app, ?*anyopaque, &onActivate, null, .{});

    const argv = init.args.vector;
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

fn onShutdown(_: *gtk.Application, data: *ShutdownData) callconv(.c) void {
    for (data.toggles_data) |toggle_data| gpa.destroy(toggle_data);
    gpa.destroy(data.widgets);
    gpa.destroy(data);

    const result = allocator.deinit();
    if (result == .leak) @panic("Leak");
}

fn onStartup(self: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    const widgets = gpa.create([6]*gtk.Widget) catch @panic("OOM");
    const shutdown_data = gpa.create(ShutdownData) catch @panic("OOM");
    const show_all_data = gpa.create(ToggleData) catch @panic("OOM");
    const show_other_data = gpa.create(ToggleData) catch @panic("OOM");
    const show_default_data = gpa.create(ToggleData) catch @panic("OOM");
    const show_fallback_data = gpa.create(ToggleData) catch @panic("OOM");
    const show_recommended_data = gpa.create(ToggleData) catch @panic("OOM");
    const window = gtk.ApplicationWindow.new(self);
    const box = gtk.Box.new(.vertical, 10);
    const app_chooser_widget = gtk.AppChooserWidget.new("image/png");
    const settings_label = gtk.Label.new("Settings:");
    const show_all_toggle = gtk.CheckButton.newWithLabel("Show all applications");
    const show_other_toggle = gtk.CheckButton.newWithLabel("Show other");
    const show_default_toggle = gtk.CheckButton.newWithLabel("Show default");
    const show_fallback_toggle = gtk.CheckButton.newWithLabel("Show fallback");
    const show_recommended_toggle = gtk.CheckButton.newWithLabel("Show recommended");

    widgets.* = .{
        app_chooser_widget.as(gtk.Widget),
        show_all_toggle.as(gtk.Widget),
        show_other_toggle.as(gtk.Widget),
        show_default_toggle.as(gtk.Widget),
        show_fallback_toggle.as(gtk.Widget),
        show_recommended_toggle.as(gtk.Widget),
    };

    shutdown_data.* = .{
        .widgets = widgets,
        .toggles_data = .{
            show_all_data,
            show_other_data,
            show_default_data,
            show_fallback_data,
            show_recommended_data,
        },
    };

    show_all_data.* = .{ .widgets = widgets, .setting = .show_all, };
    show_other_data.* = .{ .widgets = widgets, .setting = .show_other, };
    show_default_data.* = .{ .widgets = widgets, .setting = .show_default, };
    show_fallback_data.* = .{ .widgets = widgets, .setting = .show_fallback, };
    show_recommended_data.* = .{ .widgets = widgets, .setting = .show_recommended, };

    gtk.Window.setTitle(window.as(gtk.Window), APP_TITLE);
    gtk.Window.setDefaultSize(window.as(gtk.Window), 400, 400);
    gtk.Container.add(window.as(gtk.Container), box.as(gtk.Widget));
    gtk.Container.setBorderWidth(window.as(gtk.Container), 10);

    box.packStart(app_chooser_widget.as(gtk.Widget), 1, 1, 0);
    box.packStart(settings_label.as(gtk.Widget), 0, 0, 0);
    box.packStart(show_all_toggle.as(gtk.Widget), 0, 0, 0);
    box.packStart(show_default_toggle.as(gtk.Widget), 0, 0, 0);
    box.packStart(show_fallback_toggle.as(gtk.Widget), 0, 0, 0);
    box.packStart(show_other_toggle.as(gtk.Widget), 0, 0, 0);
    box.packStart(show_recommended_toggle.as(gtk.Widget), 0, 0, 0);
    gtk.Widget.showAll(box.as(gtk.Widget));

    gtk.Widget.setHalign(settings_label.as(gtk.Widget), .start);

    gtk.ToggleButton.setActive(
        show_all_toggle.as(gtk.ToggleButton),
        app_chooser_widget.getShowAll(),
    );

    gtk.ToggleButton.setActive(
        show_default_toggle.as(gtk.ToggleButton),
        app_chooser_widget.getShowDefault(),
    );

    gtk.ToggleButton.setActive(
        show_fallback_toggle.as(gtk.ToggleButton),
        app_chooser_widget.getShowFallback(),
    );

    gtk.ToggleButton.setActive(
        show_other_toggle.as(gtk.ToggleButton),
        app_chooser_widget.getShowOther(),
    );

    gtk.ToggleButton.setActive(
        show_recommended_toggle.as(gtk.ToggleButton),
        app_chooser_widget.getShowRecommended(),
    );

    _ = gio.Application.signals.shutdown.connect(
        self,
        *ShutdownData,
        onShutdown,
        shutdown_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_all_toggle,
        *ToggleData,
        onButtonToggled,
        show_all_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_other_toggle,
        *ToggleData,
        onButtonToggled,
        show_other_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_default_toggle,
        *ToggleData,
        onButtonToggled,
        show_default_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_fallback_toggle,
        *ToggleData,
        onButtonToggled,
        show_fallback_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_recommended_toggle,
        *ToggleData,
        onButtonToggled,
        show_recommended_data,
        .{},
    );
}

fn onButtonToggled(self: *gtk.CheckButton, data: *ToggleData) callconv(.c) void {
    const app_chooser_widget = gobject.ext.cast(gtk.AppChooserWidget, data.widgets.*[0]).?;
    const show_all_toggle = gobject.ext.cast(gtk.ToggleButton, data.widgets.*[1]).?;
    const is_active = gtk.ToggleButton.getActive(self.as(gtk.ToggleButton));
    const show_all = show_all_toggle.getActive();
    const setting = data.setting;

    switch (setting) {
        .show_all => {
            app_chooser_widget.setShowAll(is_active);
            if (is_active != 0) {
                for (2..6) |index| {
                    const toggle = gobject.ext.cast(gtk.ToggleButton, data.widgets.*[index]).?;
                    toggle.setActive(0);
                }
            }
        },
        .show_other => {
            app_chooser_widget.setShowOther(is_active);
            if (show_all != 0 and is_active != 0) show_all_toggle.setActive(0);
        },
        .show_default => {
            app_chooser_widget.setShowDefault(is_active);
            if (show_all != 0 and is_active != 0) show_all_toggle.setActive(0);
        },
        .show_fallback => {
            app_chooser_widget.setShowFallback(is_active);
            if (show_all != 0 and is_active != 0) show_all_toggle.setActive(0);
        },
        .show_recommended => {
            app_chooser_widget.setShowRecommended(is_active);
            if (show_all != 0 and is_active != 0) show_all_toggle.setActive(0);
        },
    }
}