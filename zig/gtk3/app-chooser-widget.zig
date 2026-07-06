const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const gobject = @import("gobject");

const AppChooserWidgetSetting = enum {
    show_all,
    show_default,
    show_fallback,
    show_other,
    show_recommended,
};

const ToggleButtonData = struct {
    widgets: []*gtk.Widget,
    setting: AppChooserWidgetSetting,
};

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.AppChooserWidget";
const APP_TITLE = "GtkAppChooserWdiget";
var allocator = std.heap.DebugAllocator(.{}).init;
const gpa = allocator.allocator();

pub fn main(init: std.process.Init.Minimal) void {
    var app = gtk.Application.new(APP_ID, .{});
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

fn onStartup(self: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    var widgets = gpa.alloc(*gtk.Widget, 6) catch @panic("OOM");
    var free_data = gpa.alloc(*anyopaque, 6) catch @panic("OOM");
    var show_all_data = gpa.create(ToggleButtonData) catch @panic("OOM");
    var show_default_data = gpa.create(ToggleButtonData) catch @panic("OOM");
    var show_fallback_data = gpa.create(ToggleButtonData) catch @panic("OOM");
    var show_other_data = gpa.create(ToggleButtonData) catch @panic("OOM");
    var show_recommended_data = gpa.create(ToggleButtonData) catch @panic("OOM");
    const window = gtk.ApplicationWindow.new(self);
    const box = gtk.Box.new(.vertical, 10);
    const app_chooser_widget = gtk.AppChooserWidget.new("image/png");
    const settings_label = gtk.Label.new("Settings:");
    const show_all_toggle = gtk.CheckButton.newWithLabel("Show all applications");
    const show_default_toggle = gtk.CheckButton.newWithLabel("Show default");
    const show_fallback_toggle = gtk.CheckButton.newWithLabel("Show fallback");
    const show_other_toggle = gtk.CheckButton.newWithLabel("Show other");
    const show_recommended_toggle = gtk.CheckButton.newWithLabel("Show recommended");

    widgets[0] = app_chooser_widget.as(gtk.Widget);
    widgets[1] = show_all_toggle.as(gtk.Widget);
    widgets[2] = show_default_toggle.as(gtk.Widget);
    widgets[3] = show_fallback_toggle.as(gtk.Widget);
    widgets[4] = show_other_toggle.as(gtk.Widget);
    widgets[5] = show_recommended_toggle.as(gtk.Widget);

    show_all_data.widgets = widgets;
    show_all_data.setting = .show_all;
    show_default_data.widgets = widgets;
    show_default_data.setting = .show_default;
    show_fallback_data.widgets = widgets;
    show_fallback_data.setting = .show_fallback;
    show_other_data.widgets = widgets;
    show_other_data.setting = .show_other;
    show_recommended_data.widgets = widgets;
    show_recommended_data.setting = .show_recommended;

    free_data[0] = @ptrCast(&widgets);
    free_data[1] = show_all_data;
    free_data[2] = show_default_data;
    free_data[3] = show_fallback_data;
    free_data[4] = show_other_data;
    free_data[5] = show_recommended_data;

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

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_all_toggle,
        *ToggleButtonData,
        onButtonToggled,
        show_all_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_default_toggle,
        *ToggleButtonData,
        onButtonToggled,
        show_default_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_fallback_toggle,
        *ToggleButtonData,
        onButtonToggled,
        show_fallback_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_other_toggle,
        *ToggleButtonData,
        onButtonToggled,
        show_other_data,
        .{},
    );

    _ = gtk.ToggleButton.signals.toggled.connect(
        show_recommended_toggle,
        *ToggleButtonData,
        onButtonToggled,
        show_recommended_data,
        .{},
    );
}

fn onShutdown(_: *gtk.Application, data: *[]*anyopaque) callconv(.c) void {
    gpa.destroy(data[1]);
    gpa.destroy(data[2]);
    gpa.destroy(data[3]);
    gpa.destroy(data[4]);
    gpa.destroy(data[5]);
    gpa.free(data[0]);
    defer _ = gpa.deinit() catch @panic("Memory leak");
}

fn onButtonToggled(self: *gtk.CheckButton, data: *ToggleButtonData) callconv(.c) void {
    const widgets = data.widgets;
    const setting = data.setting;
    const app_chooser_widget = gobject.ext.cast(gtk.AppChooserWidget, widgets[0]).?;
    const show_all_toggle = gobject.ext.cast(gtk.ToggleButton, widgets[1]).?;
    const show_all = if (show_all_toggle.getActive() == 0) false else true;
    const is_active = gtk.ToggleButton.getActive(self.as(gtk.ToggleButton));

    switch (setting) {
        .show_all => {
            app_chooser_widget.setShowAll(is_active);
            if (is_active != 0) {
                for (2..6) |i| {
                    const toggle = gobject.ext.cast(gtk.ToggleButton, widgets[i]).?;
                    toggle.setActive(0);
                }
            }
        },
        .show_default => {
            app_chooser_widget.setShowDefault(is_active);
            if (show_all and is_active != 0) show_all_toggle.setActive(0);
        },
        .show_fallback => {
            app_chooser_widget.setShowFallback(is_active);
            if (show_all and is_active != 0) show_all_toggle.setActive(0);
        },
        .show_other => {
            app_chooser_widget.setShowOther(is_active);
            if (show_all and is_active != 0) show_all_toggle.setActive(0);
        },
        .show_recommended => {
            app_chooser_widget.setShowRecommended(is_active);
            if (show_all and is_active != 0) show_all_toggle.setActive(0);
        },
    }
}