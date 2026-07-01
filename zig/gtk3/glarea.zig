const std = @import("std");
const gtk = @import("gtk");
const gio = @import("gio");
const glib = @import("glib");
const gdk = @import("gdk");
const gl = @import("zgl");
const glarea = @import("glarea-shared");

const Mat4F = glarea.Mat4F;
const AppContext = glarea.AppContext;

const APP_ID = "io.github.Miqueas.GTK-Examples.Zig.Gtk3.GLArea";
const APP_TITLE = "GtkGLArea";

const mat4f_identity = Mat4F.new();
var context = AppContext.new();

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
    _ = gtk.Widget.addTickCallback(
        gl_area.as(gtk.Widget),
        &onGLAreaTickCallback,
        null,
        null
    );
    gl_area.setHasDepthBuffer(1);
    _ = gtk.GLArea.signals.render.connect(gl_area, *AppContext, &onGLAreaRender, ctx, .{});
    _ = gtk.Widget.signals.realize.connect(gl_area, *AppContext, &onGLAreaRealize, ctx, .{});
}

fn onGLAreaTickCallback(self: *gtk.Widget, _: *gdk.FrameClock, _: ?*anyopaque) callconv(.c) c_int {
    self.queueDraw();
    return 1;
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

    return 1;
}

fn onGLAreaRealize(self: *gtk.GLArea, ctx: *AppContext) callconv(.c) void {
    std.debug.print("[GtkGLArea::realize] Called\n" , .{});
    self.makeCurrent();

    if (self.getError()) |_| {
        std.debug.print("[GtkGLArea::realize] Unknown error\n", .{});
        return;
    }

    gl.loadExtensions(void, glarea.getProcAddress) catch {
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
    const vertex_shader = compileShader(.vertex, glarea.VERTEX_SHADER);
    const fragment_shader = compileShader(.fragment, glarea.FRAGMENT_SHADER);
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

    ctx.vao = gl.genVertexArray();
    gl.bindVertexArray(ctx.vao);

    const ebo = gl.genBuffer();
    gl.bindBuffer(ebo, .element_array_buffer);
    gl.bufferData(.element_array_buffer, u16, &glarea.indices, .static_draw);

    const vertices_vbo = gl.genBuffer();
    gl.bindBuffer(vertices_vbo, .array_buffer);
    gl.bufferData(.array_buffer, f32, &glarea.vertices, .static_draw);
    gl.vertexAttribPointer(vertices_index, 3, .float, false, 0, 0);
    gl.enableVertexAttribArray(vertices_index);

    const colors_vbo = gl.genBuffer();
    gl.bindBuffer(colors_vbo, .array_buffer);
    gl.bufferData(.array_buffer, f32, &glarea.colors, .static_draw);
    gl.vertexAttribPointer(colors_index, 3, .float, false, 0, 0);
    gl.enableVertexAttribArray(colors_index);
}

fn compileShader(stype: gl.ShaderType, src: []const u8) gl.Shader {
    const shader = gl.createShader(stype);
    gl.shaderSource(shader, 1, &.{ src });
    gl.compileShader(shader);
    return shader;
}