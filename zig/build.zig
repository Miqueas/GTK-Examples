const std = @import("std");
const Import = std.Build.Module.Import;
const BuildContext = struct {
    b: *std.Build,
    dir: std.Io.Dir,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    gtkModName: []const u8,
    zigGObject: *std.Build.Dependency,
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const zigGObject = b.dependency("zigGObject", .{
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
        .dir = gtk3Dir,
        .target = target,
        .optimize = optimize,
        .gtkModName = "gtk3",
        .zigGObject = zigGObject,
    });

    try genExes(.{
        .b = b,
        .dir = gtk4Dir,
        .target = target,
        .optimize = optimize,
        .gtkModName = "gtk4",
        .zigGObject = zigGObject,
    });
}

fn genExes(ctx: BuildContext) !void {
    var walker = try ctx.dir.walk(ctx.b.allocator);
    defer walker.deinit();

    while (try walker.next(ctx.b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".zig")) continue;

        const mod = ctx.b.createModule(.{
            .root_source_file = ctx.b.path(ctx.b.fmt("{s}/{s}", .{ ctx.gtkModName, path })),
            .target = ctx.target,
            .optimize = ctx.optimize,
        });

        mod.addImport("gio", ctx.zigGObject.module("gio2"));
        mod.addImport("glib", ctx.zigGObject.module("glib2"));
        mod.addImport("gobject", ctx.zigGObject.module("gobject2"));
        mod.addImport("gtk", ctx.zigGObject.module(ctx.gtkModName));

        const basename = std.mem.trimEnd(u8, path, ".zig");
        const exe = ctx.b.addExecutable(.{
            .name = ctx.b.fmt("{s}-{s}", .{ ctx.gtkModName, basename }),
            .root_module = mod,
        });
        ctx.b.installArtifact(exe);

        const exe_run = ctx.b.addRunArtifact(exe);
        const run_step = ctx.b.step(
            ctx.b.fmt("run-{s}-{s}", .{ ctx.gtkModName, basename }),
            ctx.b.fmt("Run {s}/{s}", .{ ctx.gtkModName, basename })
        );

        exe_run.step.dependOn(ctx.b.getInstallStep());
        run_step.dependOn(&exe_run.step);

        if (ctx.b.args) |args| exe_run.addArgs(args);
    }
}