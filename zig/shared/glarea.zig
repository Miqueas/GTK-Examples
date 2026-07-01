const std = @import("std");
const gl = @import("zgl");

pub const FRAGMENT_SHADER =
\\#version 100
\\precision mediump float;
\\varying vec3 color;
\\void main() {
\\  gl_FragColor = vec4(color, 1.0);
\\}
;

pub const VERTEX_SHADER =
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

pub const vertices = [_]f32{
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

pub const colors = [_]f32{
    1.0, 0.4, 0.6,
    1.0, 0.9, 0.2,
    0.7, 0.3, 0.8,
    0.5, 0.3, 1.0,

    0.2, 0.6, 1.0,
    0.6, 1.0, 0.4,
    0.6, 0.8, 0.8,
    0.4, 0.8, 0.8,
};

pub const indices = [_]u16{
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

pub fn getProcAddress(comptime _: type, name: [:0]const u8) ?gl.binding.FunctionPointer {
    const mode = std.c.RTLD { .LAZY = true };
    const handle = std.c.dlopen("libOpenGL.so", mode) orelse return null;
    const function = std.c.dlsym(handle, @ptrCast(name.ptr)) orelse return null;
    return @ptrCast(@alignCast(function));
}

pub const AppContext = struct {
    const Self = @This();

    vao: gl.VertexArray,
    program: gl.Program,
    uniform_transform: u32,
    start_time: i64,

    pub fn new() Self {
        return .{
            .vao = .invalid,
            .program = .invalid,
            .uniform_transform = 0,
            .start_time = 0,
        };
    }
};

pub const Mat4F = struct {
    const Self = @This();

    x11: f32, x21: f32, x31: f32, x41: f32,
    x12: f32, x22: f32, x32: f32, x42: f32,
    x13: f32, x23: f32, x33: f32, x43: f32,
    x14: f32, x24: f32, x34: f32, x44: f32,

    pub fn new() Self {
        return .{
            .x11 = 1, .x21 = 0, .x31 = 0, .x41 = 0,
            .x12 = 0, .x22 = 1, .x32 = 0, .x42 = 0,
            .x13 = 0, .x23 = 0, .x33 = 1, .x43 = 0,
            .x14 = 0, .x24 = 0, .x34 = 0, .x44 = 1,
        };
    }

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