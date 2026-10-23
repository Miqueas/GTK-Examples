const os = builtin.os.tag;
const std = @import("std");
const builtin = @import("builtin");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const zigGObject = b.dependency("zig_gobject", .{
        .target = target,
        .optimize = optimize,
    });

    const zgl = b.dependency("zgl", .{
        .target = target,
        .optimize = optimize,
    });

    const gtk3Sources = try b.root.openDir(b.graph.io, "gtk3", .{ .iterate = true });
    const gtk4Sources = try b.root.openDir(b.graph.io, "gtk4", .{ .iterate = true });

    defer {
        gtk3Sources.close(b.graph.io);
        gtk4Sources.close(b.graph.io);
    }

    try prepareExes(b, gtk3Sources, zgl, target, 3, optimize, zigGObject);
    try prepareExes(b, gtk4Sources, zgl, target, 4, optimize, zigGObject);
}

fn prepareExes(
    b: *std.Build,
    dir: std.Io.Dir,
    zgl: *std.Build.Dependency,
    target: std.Build.ResolvedTarget,
    version: u8,
    optimize: std.builtin.OptimizeMode,
    zigGObject: *std.Build.Dependency,
) !void {
    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    const gtkModName = @as([]const u8, b.fmt("gtk{}", .{version}));
    const gdkModName = @as([]const u8, b.fmt("gdk{}", .{version}));

    while (try walker.next(b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".zig")) continue;

        const isGLArea = std.mem.containsAtLeast(u8, path, 1, "glarea.zig");
        if (isGLArea and os != .linux) continue;

        const mod = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .root_source_file = b.path(b.fmt("{s}/{s}", .{ gtkModName, path })),
        });

        mod.addImport("gio", zigGObject.module("gio2"));
        mod.addImport("glib", zigGObject.module("glib2"));
        mod.addImport("gobject", zigGObject.module("gobject2"));
        mod.addImport("gdk", zigGObject.module(gdkModName));
        mod.addImport("gtk", zigGObject.module(gtkModName));

        if (isGLArea) {
            mod.addImport("zgl", zgl.module("zgl"));

            // Shared code for the GtkGLArea examples
            const glareaShared = b.createModule(.{
                .target = target,
                .optimize = optimize,
                .root_source_file = b.path("shared/glarea.zig"),
            });

            glareaShared.addImport("zgl", zgl.module("zgl"));
            mod.addImport("glarea-shared", glareaShared);
        }

        const basename = std.mem.cutSuffix(u8, path, ".zig").?;
        const exe = b.addExecutable(.{
            .name = basename,
            .use_lld = if (isGLArea) true else null,
            .use_llvm = if (isGLArea) true else null,
            .root_module = mod,
        });

        const installExe = b.addInstallArtifact(exe, .{
            .dest_sub_path = b.fmt("{s}/{s}", .{ gtkModName, exe.name }),
        });

        b.getInstallStep().dependOn(&installExe.step);

        const exeRun = b.addRunArtifact(exe);
        const runStep = b.step(
            b.fmt("run-{s}-{s}", .{ gtkModName, basename }),
            b.fmt("Run {s}/{s}", .{ gtkModName, basename })
        );

        exeRun.step.dependOn(b.getInstallStep());
        runStep.dependOn(&exeRun.step);

        exeRun.addPassthruArgs();
    }
}