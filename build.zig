const std = @import("std");
const builtin = @import("builtin");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // First generate the required Zig bindings for GTK and related libraries
    const zigGTKExamplesBindings = b.addSystemCommand(&.{
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
    zigGTKExamplesBindings.setCwd(b.path("zig-gobject"));

    // We then build the Zig GTK examples
    const zigGTKExamplesBuild = b.addSystemCommand(&.{ b.graph.zig_exe, "build", });
    zigGTKExamplesBuild.setCwd(b.path("zig"));
    zigGTKExamplesBuild.step.dependOn(&zigGTKExamplesBindings.step);

    // And finally we use a step to make building the Zig GTK examples optional
    const zigGTKExamplesStep = b.step("zig", "Builds the Zig GTK examples");
    zigGTKExamplesStep.dependOn(&zigGTKExamplesBuild.step);

    const cGTK3ExamplesSources = try b.root.openDir(b.graph.io, "c/gtk3", .{ .iterate = true });
    const cGTK4ExamplesSources = try b.root.openDir(b.graph.io, "c/gtk4", .{ .iterate = true });

    defer {
        cGTK3ExamplesSources.close(b.graph.io);
        cGTK4ExamplesSources.close(b.graph.io);
    }

    const cGTKExamplesStep = b.step("c", "Builds the C GTK examples");

    try cGTKExamplesPrepareExes(3, b, cGTK3ExamplesSources, cGTKExamplesStep, target, optimize);
    try cGTKExamplesPrepareExes(4, b, cGTK4ExamplesSources, cGTKExamplesStep, target, optimize);

    const cppGTK3ExamplesSources = try b.root.openDir(b.graph.io, "cpp/gtk3", .{ .iterate = true });
    const cppGTK4ExamplesSources = try b.root.openDir(b.graph.io, "cpp/gtk4", .{ .iterate = true });

    defer {
        cppGTK3ExamplesSources.close(b.graph.io);
        cppGTK4ExamplesSources.close(b.graph.io);
    }

    const cppGTKExamplesStep = b.step("cpp", "Builds the C++ GTK examples");

    try cppGTKExamplesPrepareExes(3, b, cppGTK3ExamplesSources, cppGTKExamplesStep, target, optimize);
    try cppGTKExamplesPrepareExes(4, b, cppGTK4ExamplesSources, cppGTKExamplesStep, target, optimize);

    const valaGTK3ExamplesSources = try b.root.openDir(b.graph.io, "vala/gtk3", .{ .iterate = true });
    const valaGTK4ExamplesSources = try b.root.openDir(b.graph.io, "vala/gtk4", .{ .iterate = true });

    defer {
        valaGTK3ExamplesSources.close(b.graph.io);
        valaGTK4ExamplesSources.close(b.graph.io);
    }

    const valaGTKExamplesStep = b.step("vala", "Builds the Vala GTK examples");

    try valaGTKExamplesPrepareExes(3, b, valaGTK3ExamplesSources, valaGTKExamplesStep, target, optimize);
    try valaGTKExamplesPrepareExes(4, b, valaGTK4ExamplesSources, valaGTKExamplesStep, target, optimize);

    const allGTKExamplesStep = b.step("all", "Builds all the GTK examples (C, C++, Vala, and Zig)");
    allGTKExamplesStep.dependOn(zigGTKExamplesStep);
    allGTKExamplesStep.dependOn(cGTKExamplesStep);
    allGTKExamplesStep.dependOn(cppGTKExamplesStep);
    allGTKExamplesStep.dependOn(valaGTKExamplesStep);
}

fn cGTKExamplesPrepareExes(
    v: u4,
    b: *std.Build,
    dir: std.Io.Dir,
    step: *std.Build.Step,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) !void {
    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    const libName = switch (v) {
        3 => "gtk+-3.0",
        4 => "gtk4",
        else => @panic("Unsupported GTK version"),
    };

    while (try walker.next(b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".c")) continue;

        const isGLArea = std.mem.containsAtLeast(u8, path, 1, "glarea");
        if (isGLArea and target.result.os.tag != .linux) continue;

        const mod = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        });

        const filePath = b.fmt("c/gtk{}/{s}", .{ v, path });
        mod.addCSourceFile(.{ .file = b.path(filePath), .flags = &.{ "-std=c11" } });
        mod.linkSystemLibrary(libName, .{ .needed = true });

        if (isGLArea) {
            // It worked for me without this, but if something goes wrong for you, try using it.
            // mod.linkSystemLibrary("m", .{ .needed = true });
            mod.linkSystemLibrary("epoxy", .{ .needed = true });
        }

        const basename = path[0..(path.len - 2)];
        const exe = b.addExecutable(.{
            .name = b.fmt("{s}", .{ basename }),
            // It worked for me without this, but if something goes wrong for you, try using it.
            // .use_lld = true,
            // .use_llvm = true,
            .root_module = mod,
        });

        const installExe = b.addInstallArtifact(exe, .{
            .dest_sub_path = b.fmt("c/gtk{}/{s}", .{ v, basename }),
        });

        step.dependOn(&installExe.step);
    }
}

fn cppGTKExamplesPrepareExes(
    v: u4,
    b: *std.Build,
    dir: std.Io.Dir,
    step: *std.Build.Step,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) !void {
    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    const libName = b.fmt("gtkmm-{}.0", .{ v });
    const pkgConfPath = b.findProgram(.{ .names = &.{ "pkgconf", "pkg-config" }});
    const cppCompilerPath = b.findProgram(.{ .names = &.{ "g++", "clang++" } });

    if (pkgConfPath == null) @panic("No build-dependency configuration tool found");
    if (cppCompilerPath == null) @panic("No C++ compiler found");

    const gtkmmFlags = b.run(&.{ pkgConfPath.?, "--cflags", "--libs", libName });

    while (try walker.next(b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".cpp")) continue;

        const isGLArea = std.mem.containsAtLeast(u8, path, 1, "glarea");
        if (isGLArea and target.result.os.tag != .linux) continue;

        const basename = path[0..(path.len - 4)];
        const cpp = b.addSystemCommand(&.{ cppCompilerPath.?, "-std=c++23" });
        cpp.addArg(switch (optimize) {
            .small => "-Os",
            .debug => "-O0",
            .safe, .fast => "-O2",
        });

        if (optimize == .debug) cpp.addArg("-g");

        var gtkmmFlagsIter = std.mem.tokenizeAny(u8, gtkmmFlags, &std.ascii.whitespace);
        while (gtkmmFlagsIter.next()) |flag| cpp.addArg(flag);

        cpp.addFileArg2(b.path(b.fmt("cpp/gtk{}/{s}", .{ v, path })), .{});
        cpp.addArg("-o");

        const out = cpp.addOutputFileArg2(basename, .{});
        const install = b.addInstallBinFile(out, b.fmt("cpp/gtk{}/{s}", .{ v, basename }));

        step.dependOn(&install.step);
    }
}

fn valaGTKExamplesPrepareExes(
    v: u4,
    b: *std.Build,
    dir: std.Io.Dir,
    step: *std.Build.Step,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) !void {
    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    const libName = switch (v) {
        3 => "gtk+-3.0",
        4 => "gtk4",
        else => @panic("Unsupported GTK version"),
    };

    const optimizeFlag = switch (optimize) {
        .small => "-Os",
        .debug => "-O0",
        .safe, .fast => "-O2",
    };

    const pkgConfPath = b.findProgram(.{ .names = &.{ "pkgconf", "pkg-config" }});
    const valaCompilerPath = b.findProgram(.{ .names = &.{ "valac", } });
    const glibCompileResourcesPath = b.findProgram(.{ .names = &.{ "glib-compile-resources" } });

    if (pkgConfPath == null) @panic("No build-dependency configuration tool found");
    if (valaCompilerPath == null) @panic("No Vala compiler found");
    if (glibCompileResourcesPath == null) @panic("No GResource compiler found");

    const gtkFlagsString = b.run(&.{ pkgConfPath.?, "--cflags", "--libs", libName });

    // Generates C code from the GResource (required for the `gtk3/template.vala` example)
    const glibCompileResourcesC = b.addSystemCommand(&.{ glibCompileResourcesPath.? });
    glibCompileResourcesC.addFileArg2(b.path("data/resources.xml"), .{});
    glibCompileResourcesC.addArg("--sourcedir");
    glibCompileResourcesC.addDirectoryArg2(b.path("data/"), .{});
    glibCompileResourcesC.addArgs(&.{ "--internal", "--generate", "--target" });
    const resourcesC = glibCompileResourcesC.addOutputFileArg("resources.c");

    // Compiles the `resources.c` without linking
    const resourcesOZigCC = b.addSystemCommand(&.{ b.graph.zig_exe, "cc", "-std=c11" });
    resourcesOZigCC.step.dependOn(&glibCompileResourcesC.step);
    resourcesOZigCC.addArg(optimizeFlag);
    if (optimize == .debug) resourcesOZigCC.addArg("-g");

    var gtkFlags = std.ArrayList([]const u8).empty;
    defer gtkFlags.deinit(b.allocator);

    var gtkFlagsIter = std.mem.tokenizeAny(u8, gtkFlagsString, &std.ascii.whitespace);
    while (gtkFlagsIter.next()) |flag| try gtkFlags.append(b.allocator, flag);

    resourcesOZigCC.addArgs(gtkFlags.items);
    resourcesOZigCC.addArg("-c");
    resourcesOZigCC.addFileArg2(resourcesC, .{});
    resourcesOZigCC.addArg("-o");
    const resourcesO = resourcesOZigCC.addOutputFileArg2("resources.o", .{});

    const valaOutPathName = b.fmt("vala-out/gtk{}", .{ v });
    const valaOutPath = b.path(valaOutPathName);
    _ = b.run(&.{ "mkdir", "-p", valaOutPathName });

    while (try walker.next(b.graph.io)) |entry| {
        if (entry.kind != .file) continue;

        const path = entry.path;
        if (!std.mem.endsWith(u8, path, ".vala")) continue;

        const isGLArea = std.mem.containsAtLeast(u8, path, 1, "glarea");
        if (isGLArea and target.result.os.tag != .linux) continue;

        const basename = path[0..(path.len - 5)];
        const isTemplate = std.mem.containsAtLeast(u8, path, 1, "template");

        const valaCGen = b.addSystemCommand(&.{ valaCompilerPath.? });
        valaCGen.setCwd(valaOutPath);
        valaCGen.addArgs(&.{ "-C", "--pkg", libName });

        if (isTemplate) {
            valaCGen.step.dependOn(&resourcesOZigCC.step);
            valaCGen.addArg("--gresources");
            valaCGen.addFileArg2(b.path("data/resources.xml"), .{});
            valaCGen.addArg("--gresourcesdir");
            valaCGen.addDirectoryArg2(b.path("data/"), .{});
        }

        valaCGen.addFileArg2(b.path(b.fmt("vala/gtk{}/{s}", .{ v, path })), .{});

        const valaCFilePath = valaOutPath.path(b, b.fmt("{s}.c", .{ basename }));
        const valaCCodeZigCC = b.addSystemCommand(&.{ b.graph.zig_exe, "cc" });
        valaCCodeZigCC.step.dependOn(&valaCGen.step);
        valaCCodeZigCC.addArgs(&.{ "-std=c11", optimizeFlag });
        if (optimize == .debug) valaCCodeZigCC.addArg("-g");
        valaCCodeZigCC.addArgs(gtkFlags.items);
        valaCCodeZigCC.addArg("-c");
        valaCCodeZigCC.addFileArg2(valaCFilePath, .{});
        valaCCodeZigCC.addArg("-o");
        const valaO = valaCCodeZigCC.addOutputFileArg2(b.fmt("{s}.o", .{ basename }), .{});

        const zigCC = b.addSystemCommand(&.{ b.graph.zig_exe, "cc" });
        zigCC.step.dependOn(&valaCCodeZigCC.step);
        zigCC.addArgs(&.{ "-std=c11", optimizeFlag });
        if (optimize == .debug) zigCC.addArg("-g");
        zigCC.addArgs(gtkFlags.items);
        if (isTemplate) zigCC.addFileArg2(resourcesO, .{});
        zigCC.addFileArg2(valaO, .{});
        zigCC.addArg("-o");
        const bin = zigCC.addOutputFileArg2(basename, .{});
        const install = b.addInstallBinFile(bin, b.fmt("vala/gtk{}/{s}", .{ v, basename }));

        step.dependOn(&install.step);
    }
}