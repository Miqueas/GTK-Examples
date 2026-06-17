const std = @import("std");

pub fn build(b: *std.Build) void {
    // Generates bindings first
    const codegen = b.addSystemCommand(&.{
        b.graph.zig_exe,
        "build", "codegen",
        "-Dmodules=Gtk-3.0",
        "-Dmodules=Gtk-4.0",
        "-Dmodules=Gdk-3.0",
        "-Dmodules=Gdk-4.0",
        "-Dmodules=Gio-2.0",
        "-Dmodules=GLib-2.0",
        "-Dmodules=GObject-2.0",
    });
    codegen.setCwd(b.path("zig-gobject"));

    // Then builds the examples
    const project = b.addSystemCommand(&.{
        b.graph.zig_exe,
        "build",
    });
    project.setCwd(b.path("zig"));
    project.step.dependOn(&codegen.step);

    // Ensures previous steps are properly executed when running `zig build`
    b.getInstallStep().dependOn(&project.step);
}