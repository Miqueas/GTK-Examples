const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const glib = @import("glib");
const gdk = @import("gdk");
const gl = @import("zgl");

const AppContext = struct {
    program: gl.Program,
    vao: gl.VertexArray,
    uniform_transform: u32,
    start_time: i64,
};

const Mat4F = struct {
    const Self = @This();

    x11: f32, x21: f32, x31: f32, x41: f32,
    x12: f32, x22: f32, x32: f32, x42: f32,
    x13: f32, x23: f32, x33: f32, x43: f32,
    x14: f32, x24: f32, x34: f32, x44: f32,

    pub fn multiply(a: Self, b: Self) Self {
        return .{
            .x11 = a.x11 * b.x11 + a.x12 * b.x21 + a.x13 * b.x31 + a.x14 * b.x41,
            .x21 = a.x21 * b.x11 + a.x22 * b.x21 + a.x23 * b.x31 + a.x24 * b.x41,
            .x31 = a.x31 * b.x11 + a.x32 * b.x21 + a.x33 * b.x31 + a.x34 * b.x41,
            .x41 = a.x41 * b.x11 + a.x42 * b.x21 + a.x43 * b.x31 + a.x44 * b.x41,

            .x12 = a.x11 * b.x12 + a.x12 * b.x22 + a.x13 * b.x32 + a.x14 * b.x42,
            .x22 = a.x21 * b.x12 + a.x22 * b.x22 + a.x23 * b.x32 + a.x24 * b.x42,
            .x32 = a.x31 * b.x12 + a.x32 * b.x22 + a.x33 * b.x32 + a.x34 * b.x42,
            .x42 = a.x41 * b.x12 + a.x42 * b.x22 + a.x43 * b.x32 + a.x44 * b.x42,

            .x13 = a.x11 * b.x13 + a.x12 * b.x23 + a.x13 * b.x33 + a.x14 * b.x43,
            .x23 = a.x21 * b.x13 + a.x22 * b.x23 + a.x23 * b.x33 + a.x24 * b.x43,
            .x33 = a.x31 * b.x13 + a.x32 * b.x23 + a.x33 * b.x33 + a.x34 * b.x43,
            .x43 = a.x41 * b.x13 + a.x42 * b.x23 + a.x43 * b.x33 + a.x44 * b.x43,

            .x14 = a.x11 * b.x14 + a.x12 * b.x24 + a.x13 * b.x34 + a.x14 * b.x44,
            .x24 = a.x21 * b.x14 + a.x22 * b.x24 + a.x23 * b.x34 + a.x24 * b.x44,
            .x34 = a.x31 * b.x14 + a.x32 * b.x24 + a.x33 * b.x34 + a.x34 * b.x44,
            .x44 = a.x41 * b.x14 + a.x42 * b.x24 + a.x43 * b.x34 + a.x44 * b.x44,
        };
    }

    pub fn translation(x: f32, y: f32, z: f32) Self {
        return .{
            .x11 = 1, .x21 = 0, .x31 = 0, .x41 = 0,
            .x12 = 0, .x22 = 1, .x32 = 0, .x42 = 0,
            .x13 = 0, .x23 = 0, .x33 = 1, .x43 = 0,
            .x14 = x, .x24 = y, .x34 = z, .x44 = 1,
        };
    }

    pub fn rotateY(theta: f32) Self {
        return .{
            .x11 = std.math.cos(theta), .x21 = 0, .x31 = -std.math.sin(theta), .x41 = 0,
            .x12 = 0, .x22 = 1, .x32 = 0, .x42 = 0,
            .x13 = std.math.sin(theta), .x23 = 0, .x33 = std.math.cos(theta), .x43 = 0,
            .x14 = 0, .x24 = 0, .x34 = 0, .x44 = 1,
        };
    }

    pub fn rotateX(theta: f32) Self {
        return .{
            .x11 = 1, .x21 = 0, .x31 = 0, .x41 = 0,
            .x12 = 0, .x22 = std.math.cos(theta), .x32 = std.math.sin(theta), .x42 = 0,
            .x13 = 0, .x23 = -std.math.sin(theta), .x33 = std.math.cos(theta), .x43 = 0,
            .x14 = 0, .x24 = 0, .x34 = 0, .x44 = 1,
        };
    }

    pub fn perspective() Self {
        const r: f32 = 0.5;
        const t: f32 = 0.5;
        const n: f32 = 1;
        const f: f32 = 5;

        return .{
            .x11 = n / r, .x21 = 0, .x31 = 0, .x41 = 0,
            .x12 = 0, .x22 = n / t, .x32 = 0, .x42 = 0,
            .x13 = 0, .x23 = 0, .x33 = (-f - n) / (f - n), .x43 = -1,
            .x14 = 0, .x24 = 0, .x34 = (2 * f * n) / (n - f), .x44 = 0,
        };
    }
};

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.GLArea";
const APP_TITLE = "GtkGLArea";
const FRAGMENT_SHADER =
\\#version 100
\\precision mediump float;
\\varying vec3 color;
\\void main() {
\\  gl_FragColor = vec4(color, 1.0);
\\}
;

const VERTEX_SHADER =
\\#version 100
\\precision mediump float;
\\attribute vec3 pos;
\\attribute vec3 vertex_color;
\\uniform mat4 transform;
\\varying vec3 color;
\\void main() {
\\  gl_Position = transform * vec4(pos, 1.0);
\\  color = vertex_color;
\\}
;

const mat4f_identity = Mat4F {
    .x11 = 1, .x21 = 0, .x31 = 0, .x41 = 0,
    .x12 = 0, .x22 = 1, .x32 = 0, .x42 = 0,
    .x13 = 0, .x23 = 0, .x33 = 1, .x43 = 0,
    .x14 = 0, .x24 = 0, .x34 = 0, .x44 = 1,
};

var context = AppContext {
    .program = .invalid,
    .vao = .invalid,
    .uniform_transform = 0,
    .start_time = 0,
};

pub fn main(init: std.process.Init) void {
    var app = gtk.Application.new(APP_ID, .{});
    defer app.unref();

    _ = gio.Application.signals.startup.connect(app, *AppContext, &onStartup, &context, .{});
    _ = gio.Application.signals.activate.connect(app, ?*anyopaque, &onActivate, null, .{});

    const argv = init.minimal.args.vector;
    const status = gio.Application.run(
        app.as(gio.Application),
        @intCast(argv.len),
        @ptrCast(@constCast(argv.ptr))
    );

    std.process.exit(@intCast(status));
}

fn onActivate(self: *gtk.Application, _: ?*anyopaque) callconv(.c) void {
    if (self.getActiveWindow()) |window| window.present();
}

fn onStartup(self: *gtk.Application, ctx: *AppContext) callconv(.c) void {
    var window = gtk.ApplicationWindow.new(self);
    var gl_area = gtk.GLArea.new();

    gtk.Window.setTitle(window.as(gtk.Window), APP_TITLE);
    gtk.Window.setDefaultSize(window.as(gtk.Window), 400, 400);
    gtk.Container.add(window.as(gtk.Container), gl_area.as(gtk.Widget));

    gtk.Widget.show(gl_area.as(gtk.Widget));
    gtk.Widget.setVexpand(gl_area.as(gtk.Widget), gtk.@"true"());
    gtk.Widget.setHexpand(gl_area.as(gtk.Widget), gtk.@"true"());
    _ = gtk.Widget.addTickCallback(
        gl_area.as(gtk.Widget),
        &onGLAreaTickCallback,
        null,
        null
    );
    gl_area.setHasDepthBuffer(gtk.@"true"());
    _ = gtk.GLArea.signals.render.connect(gl_area, *AppContext, &onGLAreaRender, ctx, .{});
    _ = gtk.Widget.signals.realize.connect(gl_area, *AppContext, &onGLAreaRealize, ctx, .{});
}

fn onGLAreaTickCallback(self: *gtk.Widget, _: *gdk.FrameClock, _: ?*anyopaque) callconv(.c) c_int {
    self.queueDraw();
    return gtk.@"true"();
}

fn onGLAreaRender(_: *gtk.GLArea, _: *gdk.GLContext, ctx: *AppContext) callconv(.c) c_int {
    gl.clearColor(0.1, 0.12, 0.2, 1);
    gl.clear(.{ .color = true, .depth = true });
    gl.useProgram(ctx.program);

    const now = glib.getMonotonicTime();
    const delta = now - ctx.start_time;
    const time_seconds = @as(f32, @floatFromInt(delta)) / 1_000_000.0;
    const rotation = @rem(time_seconds, 10.0) / 10.0 * 2.0 * std.math.pi;
    var transform = mat4f_identity;
    transform = transform.multiply(Mat4F.perspective());
    transform = transform.multiply(Mat4F.translation(0, 0, -3));
    transform = transform.multiply(Mat4F.rotateX(0.15 * std.math.pi));
    transform = transform.multiply(Mat4F.rotateY(rotation));

    const matrix = @as([]const [4][4]f32, @ptrCast(&transform));
    gl.uniformMatrix4fv(ctx.uniform_transform, false, matrix);
    gl.bindVertexArray(ctx.vao);
    gl.drawElements(.triangles, 48, .unsigned_short, 0);

    return gtk.@"true"();
}

fn onGLAreaRealize(self: *gtk.GLArea, ctx: *AppContext) callconv(.c) void {
    std.debug.print("[GtkGLArea::realize] Called\n" , .{});
    self.makeCurrent();

    if (self.getError()) |_| {
        std.debug.print("[GtkGLArea::realize] Unknown error\n", .{});
        return;
    }

    gl.loadExtensions(void, getProcAddress) catch {
        std.debug.print("[GtkGLArea::realize] Failed to load GL functions", .{});
        return;
    };

    const renderer = gl.getString(.renderer);
    const version = gl.getString(.version);

    if (renderer) |r| std.debug.print("[GtkGLArea::realize] Renderer: {s}\n", .{ r });
    if (version) |v| std.debug.print("[GtkGLArea::realize] Version: {s}\n", .{ v });

    gl.enable(.depth_test);
    initShaders(ctx);
    initBuffers(ctx);

    gl.bindVertexArray(.invalid);
    gl.bindBuffer(.invalid, .element_array_buffer);
    gl.bindBuffer(.invalid, .array_buffer);

    ctx.start_time = glib.getMonotonicTime();
}

fn initShaders(ctx: *AppContext) void {
    const vertex_shader = compileShader(.vertex, VERTEX_SHADER);
    const fragment_shader = compileShader(.fragment, FRAGMENT_SHADER);
    ctx.program = gl.createProgram();
    gl.attachShader(ctx.program, vertex_shader);
    gl.attachShader(ctx.program, fragment_shader);
    gl.bindAttribLocation(ctx.program, 0, "pos");
    gl.bindAttribLocation(ctx.program, 1, "vertex_color");
    gl.linkProgram(ctx.program);
    gl.deleteShader(vertex_shader);
    gl.deleteShader(fragment_shader);
    ctx.uniform_transform = gl.getUniformLocation(ctx.program, "transform").?;
}

fn initBuffers(ctx: *AppContext) void {
    const vertices_index: u32 = 0;
    const colors_index: u32 = 1;
    const vertices = [_]f32{
        // Front
         0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
        -0.5, -0.5,  0.5,
         0.5, -0.5,  0.5,
        // Back
         0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,
         0.5, -0.5, -0.5,
    };

    const vertex_colors = [_]f32{
        1.0, 0.4, 0.6,
        1.0, 0.9, 0.2,
        0.7, 0.3, 0.8,
        0.5, 0.3, 1.0,

        0.2, 0.6, 1.0,
        0.6, 1.0, 0.4,
        0.6, 0.8, 0.8,
        0.4, 0.8, 0.8,
    };

    const indices = [_]u16{
        // Front
        0, 1, 2,
        2, 3, 0,
        // Right
        0, 3, 7,
        7, 4, 0,
        // Bottom
        2, 6, 7,
        7, 3, 2,
        // Left
        1, 5, 6,
        6, 2, 1,
        // Back
        4, 7, 6,
        6, 5, 4,
        // Top
        5, 1, 0,
        0, 4, 5,
    };

    ctx.vao = gl.genVertexArray();
    gl.bindVertexArray(ctx.vao);

    const ebo = gl.genBuffer();
    gl.bindBuffer(ebo, .element_array_buffer);
    gl.bufferData(.element_array_buffer, u16, &indices, .static_draw);

    const vertices_vbo = gl.genBuffer();
    gl.bindBuffer(vertices_vbo, .array_buffer);
    gl.bufferData(.array_buffer, f32, &vertices, .static_draw);
    gl.vertexAttribPointer(vertices_index, 3, .float, false, 0, 0);
    gl.enableVertexAttribArray(vertices_index);

    const colors_vbo = gl.genBuffer();
    gl.bindBuffer(colors_vbo, .array_buffer);
    gl.bufferData(.array_buffer, f32, &vertex_colors, .static_draw);
    gl.vertexAttribPointer(colors_index, 3, .float, false, 0, 0);
    gl.enableVertexAttribArray(colors_index);
}

fn compileShader(stype: gl.ShaderType, src: []const u8) gl.Shader {
    const shader = gl.createShader(stype);
    gl.shaderSource(shader, 1, &.{ src });
    gl.compileShader(shader);
    return shader;
}

fn getProcAddress(comptime _: type, name: [:0]const u8) ?gl.binding.FunctionPointer {
    // var buf: [256:0]u8 = undefined;
    // const sym = std.fmt.bufPrintSentinel(&buf, "epoxy_{s}", .{name}, 0) catch return null;
    // const mode = std.c.RTLD { .LAZY = true, .DEFAULT = true };
    // const handle = std.c.dlopen("libepoxy.so", mode) orelse return null;
    // const function = std.c.dlsym(handle, @ptrCast(sym.ptr)) orelse return null;
    // return @ptrCast(@alignCast(function));
    const mode = std.c.RTLD { .LAZY = true };
    const handle = std.c.dlopen("libOpenGL.so", mode) orelse return null;
    const function = std.c.dlsym(handle, @ptrCast(name.ptr)) orelse return null;
    return @ptrCast(@alignCast(function));
}