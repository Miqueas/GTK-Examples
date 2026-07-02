const std = @import("std");
const builtin = @import("builtin");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Generate bindings first
    const codegen = b.addSystemCommand(&.{
        b.graph.zig_exe,
        "build", "codegen",
        "-Dmodules=Gtk-3.0",
        "-Dmodules=Gdk-3.0",
        "-Dmodules=Gtk-4.0",
        "-Dmodules=Gdk-4.0",
        "-Dmodules=Gio-2.0",
        "-Dmodules=GLib-2.0",
        "-Dmodules=GObject-2.0",
    });
    codegen.setCwd(b.path("zig-gobject"));

    // Then build the examples
    const project = b.addSystemCommand(&.{ b.graph.zig_exe, "build", });
    project.setCwd(b.path("zig"));
    project.step.dependOn(&codegen.step);

    // Ensures all steps are actually executed when running `zig build`
    b.getInstallStep().dependOn(&project.step);

    const c_gtk3_dir = try b.build_root.handle.openDir(b.graph.io, "c/gtk3", .{ .iterate = true });
    const c_gtk4_dir = try b.build_root.handle.openDir(b.graph.io, "c/gtk4", .{ .iterate = true });

    defer {
        c_gtk3_dir.close(b.graph.io);
        c_gtk4_dir.close(b.graph.io);
    }

    try genCExes(3, b, c_gtk3_dir, target, optimize);
    try genCExes(4, b, c_gtk4_dir, target, optimize);
}

fn genCExes(
    v: u4,
    b: *std.Build,
    dir: std.Io.Dir,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) !void {
    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    const lib_name = switch (v) {
        3 => "gtk+-3.0",
        4 => "gtk4",
        else => @panic("Unsupported GTK version"),
    };

    while (try walker.next(b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".c")) continue;

        const is_glarea = std.mem.containsAtLeast(u8, path, 1, "glarea.c");
        if (is_glarea and target.result.os.tag != .linux) continue;

        const mod = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        });

        mod.addCSourceFile(.{ .file = b.path(b.fmt("c/gtk{}/{s}", .{ v, path })), });
        mod.linkSystemLibrary(lib_name, .{ .needed = true });

        if (is_glarea) {
            // It worked for me without this, but if something goes wrong for you, try using it.
            // mod.linkSystemLibrary("m", .{ .needed = true });
            mod.linkSystemLibrary("epoxy", .{ .needed = true });
        }

        const basename = std.mem.trimEnd(u8, path, ".c");
        const exe = b.addExecutable(.{
            .name = b.fmt("c-gtk{}-{s}", .{ v, basename }),
            // It worked for me without this, but if something goes wrong for you, try using it.
            // .use_lld = true,
            // .use_llvm = true,
            .root_module = mod,
        });

        b.installArtifact(exe);
    }
}