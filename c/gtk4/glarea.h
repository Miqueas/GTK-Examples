#include <gtk/gtk.h>
#include <epoxy/gl.h>
#include <math.h>

static const gchar* FRAGMENT_SHADER = "#version 100\n"
"precision mediump float;\n"
"varying vec3 color;\n"
"void main() {\n"
"  gl_FragColor = vec4(color, 1.0);\n"
"}";

static const gchar* VERTEX_SHADER = "#version 100\n"
"precision mediump float;\n"
"attribute vec3 pos;\n"
"attribute vec3 vertex_color;\n"
"uniform mat4 transform;\n"
"varying vec3 color;\n"
"void main() {\n"
"  gl_Position = transform * vec4(pos, 1.0);\n"
"  color = vertex_color;\n"
"}";

static const GLfloat vertices[] = {
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

static const GLfloat vertex_colors[] = {
  1.0, 0.4, 0.6,
  1.0, 0.9, 0.2,
  0.7, 0.3, 0.8,
  0.5, 0.3, 1.0,

  0.2, 0.6, 1.0,
  0.6, 1.0, 0.4,
  0.6, 0.8, 0.8,
  0.4, 0.8, 0.8,
};

static const GLushort indices[] = {
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

typedef struct {
  GLuint vao, program, uniform_transform;
  gint64 start_time;
} AppContext;

typedef struct {
  // Column-major order
  float x11, x21, x31, x41;
  float x12, x22, x32, x42;
  float x13, x23, x33, x43;
  float x14, x24, x34, x44;
} Mat4F;

Mat4F mat4f_new() {
  return (Mat4F) {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
}

// Return the given matrix in a format understood by OpenGL.
float* mat4f_to_gl(Mat4F* m) {
  // Since it's already in colum-major order, we just return the address of the
  // first element.
  return &m->x11;
}

Mat4F mat4f_multiply(Mat4F a, Mat4F b) {
  return (Mat4F) {
    a.x11 * b.x11 + a.x12 * b.x21 + a.x13 * b.x31 + a.x14 * b.x41,
    a.x21 * b.x11 + a.x22 * b.x21 + a.x23 * b.x31 + a.x24 * b.x41,
    a.x31 * b.x11 + a.x32 * b.x21 + a.x33 * b.x31 + a.x34 * b.x41,
    a.x41 * b.x11 + a.x42 * b.x21 + a.x43 * b.x31 + a.x44 * b.x41,

    a.x11 * b.x12 + a.x12 * b.x22 + a.x13 * b.x32 + a.x14 * b.x42,
    a.x21 * b.x12 + a.x22 * b.x22 + a.x23 * b.x32 + a.x24 * b.x42,
    a.x31 * b.x12 + a.x32 * b.x22 + a.x33 * b.x32 + a.x34 * b.x42,
    a.x41 * b.x12 + a.x42 * b.x22 + a.x43 * b.x32 + a.x44 * b.x42,

    a.x11 * b.x13 + a.x12 * b.x23 + a.x13 * b.x33 + a.x14 * b.x43,
    a.x21 * b.x13 + a.x22 * b.x23 + a.x23 * b.x33 + a.x24 * b.x43,
    a.x31 * b.x13 + a.x32 * b.x23 + a.x33 * b.x33 + a.x34 * b.x43,
    a.x41 * b.x13 + a.x42 * b.x23 + a.x43 * b.x33 + a.x44 * b.x43,

    a.x11 * b.x14 + a.x12 * b.x24 + a.x13 * b.x34 + a.x14 * b.x44,
    a.x21 * b.x14 + a.x22 * b.x24 + a.x23 * b.x34 + a.x24 * b.x44,
    a.x31 * b.x14 + a.x32 * b.x24 + a.x33 * b.x34 + a.x34 * b.x44,
    a.x41 * b.x14 + a.x42 * b.x24 + a.x43 * b.x34 + a.x44 * b.x44,
  };
}

Mat4F mat4f_translation(float x, float y, float z) {
  return (Mat4F) {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    x, y, z, 1,
  };
}

Mat4F mat4f_rotate_y(float theta) {
  return (Mat4F) {
    cos(theta), 0, -sin(theta), 0,
             0, 1,           0, 0,
    sin(theta), 0,  cos(theta), 0,
             0, 0,           0, 1,
  };
}

Mat4F mat4f_rotate_x(float theta) {
  return (Mat4F) {
    1, 0, 0, 0,
    0, cos(theta), sin(theta), 0,
    0, -sin(theta), cos(theta), 0,
    0, 0, 0, 1,
  };
}

Mat4F mat4f_perspective() {
  // Based on http://www.songho.ca/opengl/gl_projectionmatrix.html, which I don't
  // really understand. I just copied the final result.

  const float
    r = 0.5,  // Half of the viewport width (at the near plane)
    t = 0.5,  // Half of the viewport height (at the near plane)
    n = 1,  // Distance to near clipping plane
    f = 5;  // Distance to far clipping plane

  // Note that while n and f are given as positive integers above,
  // the camera is looking in the negative direction. So we will see
  // stuff between z = -n and z = -f.

  return (Mat4F) {
    n / r, 0, 0, 0,
    0, n / t, 0, 0,
    0, 0, (-f - n) / (f - n), -1,
    0, 0, (2 * f * n) / (n - f), 0,
  };
}