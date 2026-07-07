const os = builtin.os.tag;
const std = @import("std");
const builtin = @import("builtin");

const BuildContext = struct {
    b: *std.Build,
    dir: std.Io.Dir,
    zgl: *std.Build.Dependency,
    target: std.Build.ResolvedTarget,
    version: u8,
    optimize: std.builtin.OptimizeMode,
    zigGObject: *std.Build.Dependency,
};

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

    const gtk3Dir = try b.build_root.handle.openDir(b.graph.io, "gtk3", .{ .iterate = true });
    const gtk4Dir = try b.build_root.handle.openDir(b.graph.io, "gtk4", .{ .iterate = true });
    defer {
        gtk3Dir.close(b.graph.io);
        gtk4Dir.close(b.graph.io);
    }

    try genExes(.{
        .b = b,
        .zgl = zgl,
        .dir = gtk3Dir,
        .target = target,
        .version = 3,
        .optimize = optimize,
        .zigGObject = zigGObject,
    });

    try genExes(.{
        .b = b,
        .zgl = zgl,
        .dir = gtk4Dir,
        .target = target,
        .version = 4,
        .optimize = optimize,
        .zigGObject = zigGObject,
    });
}

fn genExes(ctx: BuildContext) !void {
    var walker = try ctx.dir.walk(ctx.b.allocator);
    defer walker.deinit();

    const gtkModName = @as([]const u8, ctx.b.fmt("gtk{}", .{ctx.version}));
    const gdkModName = @as([]const u8, ctx.b.fmt("gdk{}", .{ctx.version}));

    while (try walker.next(ctx.b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".zig")) continue;

        const isGLArea = std.mem.containsAtLeast(u8, path, 1, "glarea.zig");
        if (isGLArea and os != .linux) continue;

        const mod = ctx.b.createModule(.{
            .target = ctx.target,
            .optimize = ctx.optimize,
            .root_source_file = ctx.b.path(ctx.b.fmt("{s}/{s}", .{ gtkModName, path })),
        });

        mod.addImport("gio", ctx.zigGObject.module("gio2"));
        mod.addImport("glib", ctx.zigGObject.module("glib2"));
        mod.addImport("gobject", ctx.zigGObject.module("gobject2"));
        mod.addImport("gdk", ctx.zigGObject.module(gdkModName));
        mod.addImport("gtk", ctx.zigGObject.module(gtkModName));
        if (isGLArea) {
            mod.addImport("zgl", ctx.zgl.module("zgl"));

            const glarea_shared = ctx.b.createModule(.{
                .target = ctx.target,
                .optimize = ctx.optimize,
                .root_source_file = ctx.b.path("shared/glarea.zig"),
            });
            glarea_shared.addImport("zgl", ctx.zgl.module("zgl"));
            mod.addImport("glarea-shared", glarea_shared);
        }

        const basename = std.mem.cutSuffix(u8, path, ".zig").?;
        const exe = ctx.b.addExecutable(.{
            .name = ctx.b.fmt("{s}-{s}", .{ gtkModName, basename }),
            .use_lld = if (isGLArea) true else null,
            .use_llvm = if (isGLArea) true else null,
            .root_module = mod,
        });

        ctx.b.installArtifact(exe);

        const exe_run = ctx.b.addRunArtifact(exe);
        const run_step = ctx.b.step(
            ctx.b.fmt("run-{s}-{s}", .{ gtkModName, basename }),
            ctx.b.fmt("Run {s}/{s}", .{ gtkModName, basename })
        );

        exe_run.step.dependOn(ctx.b.getInstallStep());
        run_step.dependOn(&exe_run.step);

        if (ctx.b.args) |args| exe_run.addArgs(args);
    }
}