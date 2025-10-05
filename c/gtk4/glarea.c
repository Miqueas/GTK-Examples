// Original by:   Benjamin Collins (https://github.com/kion-dgl)
// Sources:       https://github.com/kion-dgl/DashGL-GTK-Brickout-Tutorial/blob/master/02_Draw_a_Triangle/main.c
//   -            https://dashgl.org/tutorials/gtk-invaders/step-02/
//   -            https://gtk.dashgl.com/Brickout/Draw_a_Triangle/
// Modified by:   Miqueas Martínez (https://github.com/Miqueas)
// Maintained by: Miqueas Martínez (https://github.com/Miqueas)

#include <gtk/gtk.h>
#include <epoxy/gl.h>

static void on_app_startup(GApplication* self, gpointer data);
static void on_app_activate(GApplication* self, gpointer data);
static void on_gl_area_realize(GtkGLArea* self, gint width, gint height, gpointer data);
static gboolean on_gl_area_render(GtkGLArea* self, GdkGLContext* context, gpointer data);

const static gchar* APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk4.GLArea";
const static gchar* APP_TITLE = "GtkGLArea";
const static gchar* VS_SOURCE = "#version 100\n"
"attribute vec2 coord2d;\n"
"void main (void) {\n"
"  gl_Position = vec4(coord2d, 0.0, 1.0);\n"
"}";
const static gchar* FS_SOURCE = "#version 100\n"
"void main (void) {\n"
"  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
"}";

static GLuint program, vao, vbo;
static GLint attribute_coord_2d;

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
  GtkWidget* window = gtk_application_window_new(GTK_APPLICATION(self));
  GtkWidget* gl_area = gtk_gl_area_new();

  gtk_window_set_child(GTK_WINDOW(window), gl_area);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_vexpand(gl_area, TRUE);
  gtk_widget_set_hexpand(gl_area, TRUE);
  g_signal_connect(gl_area, "realize", G_CALLBACK(on_gl_area_realize), NULL);
  g_signal_connect(gl_area, "render", G_CALLBACK(on_gl_area_render), NULL);
}

void on_gl_area_realize(GtkGLArea* self, gint width, gint height, gpointer data) {
  const GLfloat triangle_vertices[] = { 0.0, 0.8, -0.8, -0.8, 0.8, -0.8 };
  const gchar* attribute_name = "coord2d";
  GLint compile_ok = GL_FALSE;
  GLint link_ok = GL_FALSE;

  g_print("[GtkGLArea::realize] Called\n");
  gtk_gl_area_make_current(self);
  
  if (gtk_gl_area_get_error (self) != NULL) {
    g_printerr("[GtkGLArea::realize] Unknown error\n");
    return;
  }

  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);

  g_print("[GtkGLArea::realize] Renderer: %s\n", renderer);
  g_print("[GtkGLArea::realize] Version: %s\n", version);

  gtk_gl_area_set_has_depth_buffer(self, TRUE);
  
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  glDisableVertexAttribArray(0);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(fs, 1, &FS_SOURCE, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);

  if(!compile_ok) {
    GLint log_length;
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      gchar* log = g_malloc(log_length);
      glGetShaderInfoLog(fs, log_length, NULL, log);
      g_printerr("[GtkGLArea::realize] Fragment Shader error: %s\n", log);
      g_free(log);
    }

    return;
  }

  glShaderSource(vs, 1, &VS_SOURCE, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);

  if(!compile_ok) {
    GLint log_length;
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      gchar* log = g_malloc(log_length);
      glGetShaderInfoLog(vs, log_length, NULL, log);
      g_printerr("[GtkGLArea::realize] Vertex Shader error: %s\n", log);
      g_free(log);
    }

    return;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);

  if(!link_ok) {
    GLint log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0) {
      gchar* log = g_malloc(log_length);
      glGetProgramInfoLog(program, log_length, NULL, log);
      g_printerr("[GtkGLArea::realize] Program link error: %s\n", log);
      g_free(log);
    }

    return;
  }

  attribute_coord_2d = glGetAttribLocation(program, attribute_name);

  if(attribute_coord_2d == -1) {
    g_printerr("[GtkGLArea::realize] Could not bind attribute %s\n", attribute_name);
    return;
  }
}

gboolean on_gl_area_render(GtkGLArea* self, GdkGLContext* context, gpointer data) {
  g_print("[GtkGLArea::render] Called\n");

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(program);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(attribute_coord_2d);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(attribute_coord_2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attribute_coord_2d);

  return TRUE;
}