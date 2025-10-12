#include "glarea.h"

static void on_app_startup(GApplication* self, gpointer data);
static void on_app_activate(GApplication* self, gpointer data);
static void on_gl_area_realize(GtkGLArea* self, gpointer data);
static gboolean on_gl_area_render(GtkGLArea* self, GdkGLContext* context, gpointer data);
static gboolean gl_area_tick_callback(GtkWidget* self, GdkFrameClock* frame_clock, gpointer data);
static void init_shaders(AppContext* ctx);
static void init_buffers(AppContext* ctx);
static GLuint compile_shader(GLenum type, const gchar* source);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.GLArea";
const static gchar* APP_TITLE = "GtkGLArea";
const static gchar* FRAGMENT_SHADER = "#version 100\n"
"precision mediump float;\n"
"varying vec3 color;\n"
"void main() {\n"
"  gl_FragColor = vec4(color, 1.0);\n"
"}";

const static gchar* VERTEX_SHADER = "#version 100\n"
"precision mediump float;\n"
"attribute vec3 pos;\n"
"attribute vec3 vertex_color;\n"
"uniform mat4 transform;\n"
"varying vec3 color;\n"
"void main() {\n"
"  gl_Position = transform * vec4(pos, 1.0);\n"
"  color = vertex_color;\n"
"}";

gint main(gint argc, gchar** argv) {
  GtkApplication* app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(on_app_startup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;

}

static void on_app_activate(GApplication* self, gpointer data) {
  GtkWindow* window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void on_app_startup(GApplication* self, gpointer data) {
  AppContext* context = g_new0(AppContext, 1);
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* gl_area = gtk_gl_area_new();

  gtk_container_add(GTK_CONTAINER(window), gl_area);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_show(gl_area);
  gtk_widget_set_vexpand(gl_area, TRUE);
  gtk_widget_set_hexpand(gl_area, TRUE);
  gtk_widget_add_tick_callback(gl_area, gl_area_tick_callback, NULL, NULL);
  gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(gl_area), TRUE);
  g_signal_connect(gl_area, "render", G_CALLBACK(on_gl_area_render), context);
  g_signal_connect(gl_area, "realize", G_CALLBACK(on_gl_area_realize), context);
}

static void on_gl_area_realize(GtkGLArea* self, gpointer data) {
  AppContext* context = (AppContext*) data;

  g_print("[GtkGLArea::realize] Called\n");
  gtk_gl_area_make_current(self);
  
  if (gtk_gl_area_get_error (self) != NULL) {
    g_critical("[GtkGLArea::realize] Unknown error\n");
    return;
  }

  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);

  g_print("[GtkGLArea::realize] Renderer: %s\n", renderer);
  g_print("[GtkGLArea::realize] Version: %s\n", version);

  glEnable(GL_DEPTH_TEST);

  init_shaders(context);
  init_buffers(context);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  context->start_time = g_get_monotonic_time();
}

static gboolean on_gl_area_render(GtkGLArea* self, GdkGLContext* context, gpointer data) {
  AppContext* ctx = (AppContext*) data;

  glClearColor(0.1, 0.12, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(ctx->program);

  gint64 now = g_get_monotonic_time();
  gdouble time_seconds = (now - ctx->start_time) / 1000000.0;
  gfloat rotation = fmod(time_seconds, 10.0) / 10.0 * 2.0 * G_PI;

  mat4f_t transform = mat4f_identity;
  transform = mat4f_multiply(transform, mat4f_perspective());
  transform = mat4f_multiply(transform, mat4f_translation(0, 0, -3));
  transform = mat4f_multiply(transform, mat4f_rotate_x(0.15 * G_PI));
  transform = mat4f_multiply(transform, mat4f_rotate_y(rotation));

  glUniformMatrix4fv(ctx->uniform_transform, 1, GL_FALSE, mat4f_gl(&transform));
  glBindVertexArray(ctx->vao);
  glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, NULL);

  return TRUE;
}

static gboolean gl_area_tick_callback(GtkWidget* self, GdkFrameClock* frame_clock, gpointer data) {
  gtk_widget_queue_draw(self);
  return G_SOURCE_CONTINUE;
}

static void init_shaders(AppContext* ctx) {
  GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, VERTEX_SHADER);
  GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER);

  if (vertex_shader == 0 || fragment_shader == 0) {
    g_critical("[GtkGLArea::realize] Shader compilation failed\n");
    return;
  }

  ctx->program = glCreateProgram();
  glAttachShader(ctx->program, vertex_shader);
  glAttachShader(ctx->program, fragment_shader);
  
  // Bind attribute locations before linking (required for GLSL 100)
  glBindAttribLocation(ctx->program, 0, "pos");
  glBindAttribLocation(ctx->program, 1, "vertex_color");
  
  glLinkProgram(ctx->program);

  GLint status = GL_FALSE;
  glGetProgramiv(ctx->program, GL_LINK_STATUS, &status);

  if (!status) {
    GLint log_length;
    glGetProgramiv(ctx->program, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      gchar* log = g_malloc(log_length);
      glGetProgramInfoLog(ctx->program, log_length, NULL, log);
      g_critical("[GtkGLArea::realize] Link Program error: %s\n", log);
      g_free(log);
    }

    return;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  ctx->uniform_transform = glGetUniformLocation(ctx->program, "transform");
}

static void init_buffers(AppContext* ctx) {
  const GLuint vertices_index = 0;
  const GLuint colors_index = 1; 
  GLfloat vertices[] = {
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

  GLfloat vertex_colors[] = {
    1.0, 0.4, 0.6,
    1.0, 0.9, 0.2,
    0.7, 0.3, 0.8,
    0.5, 0.3, 1.0,

    0.2, 0.6, 1.0,
    0.6, 1.0, 0.4,
    0.6, 0.8, 0.8,
    0.4, 0.8, 0.8,
  };

  GLushort indices[] = {
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

  glGenVertexArrays(1, &ctx->vao);
  glBindVertexArray(ctx->vao);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  GLuint vertices_vbo;
  glGenBuffers(1, &vertices_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertices_index, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(vertices_index);

  GLuint colors_vbo;
  glGenBuffers(1, &colors_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);
  glVertexAttribPointer(colors_index, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(colors_index);
}

static GLuint compile_shader(GLenum type, const gchar* source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint status = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (!status) {
    GLint log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      gchar* log = g_malloc(log_length);
      glGetShaderInfoLog(shader, log_length, NULL, log);
      g_critical("[GtkGLArea::realize] Compile Shader error: %s\n", log);
      g_free(log);
    }

    return 0;
  }

  return shader;
}