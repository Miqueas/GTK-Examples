const std = @import("std");
const Import = std.Build.Module.Import;

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    // zig-gobject pkg dep
    const gobject = b.dependency("gobject", .{
        .target = target,
        .optimize = optimize,
    });

    const imports: []const Import = &.{
        .{ .name = "gio",     .module = gobject.module("gio2"),     },
        .{ .name = "glib",    .module = gobject.module("glib2"),    },
        .{ .name = "gobject", .module = gobject.module("gobject2"), },
        .{ .name = "gtk4",    .module = gobject.module("gtk4"),     },
        // .{ .name = "gtk3",    .module = gobject.module("gtk3"),     },
    };

    const gtk4Dir = try b.build_root.handle.openDir(b.graph.io, "gtk4", .{ .iterate = true });
    var walker = try gtk4Dir.walk(b.allocator);
    defer {
        walker.deinit();
        gtk4Dir.close(b.graph.io);
    }

    while (try walker.next(b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".zig")) continue;

        const mod = b.createModule(.{
            .root_source_file = b.path(b.fmt("gtk4/{s}", .{ path })),
            .target = target,
            .imports = imports,
            .optimize = optimize,
        });

        const basename = std.mem.trimEnd(u8, path, ".zig");
        const exe = b.addExecutable(.{ .name = basename, .root_module = mod, });
        b.installArtifact(exe);

        const exe_run = b.addRunArtifact(exe);
        const run_step = b.step(b.fmt("run-{s}", .{ basename }), b.fmt("Run {s}", .{ basename }));

        exe_run.step.dependOn(b.getInstallStep());
        run_step.dependOn(&exe_run.step);

        if (b.args) |args| exe_run.addArgs(args);
    }
}