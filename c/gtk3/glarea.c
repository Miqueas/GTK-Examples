/*****************************************************************************
 * DashGL.com GTK GL-Area                                                    *
 * This file is in the public domain                                         *
 * Contributors: Benjamin Collins                                            *
 *****************************************************************************/

#include <gtk/gtk.h>
#include <epoxy/gl.h>

void onAppStartup(GApplication *self, gpointer data);
void onAppActivate(GApplication *self, gpointer data);
void onGLAreaRealize(GtkGLArea *self, gint width, gint height, gpointer data);
gboolean onGLAreaRender(GtkGLArea *self, GdkGLContext *context, gpointer data);

const gchar *APP_ID = "io.github.Miqueas.GTK-Examples.C.Gtk3.GLArea";
const gchar *APP_TITLE = "GtkGLArea";

const char *vsSource = "#version 100\n"
"attribute vec2 coord2d;\n"
"void main (void) {\n"
"  gl_Position = vec4(coord2d, 0.0, 1.0);\n"
"}";

const char *fsSource = "#version 100\n"
"void main (void) {\n"
"  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
"}";

GLuint program, vao, vbo;
GLint attributeCoord2D;

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new(APP_ID, 0);
  g_signal_connect(app, "startup", G_CALLBACK(onAppStartup), NULL);
  g_signal_connect(app, "activate", G_CALLBACK(onAppActivate), NULL);

  int result = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return result;

}

void onAppActivate(GApplication *self, gpointer data) {
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(window);
}

void onAppStartup(GApplication *self, gpointer data) {
  GtkWidget *window, *glArea;

  window = gtk_application_window_new(GTK_APPLICATION(self));
  glArea = gtk_gl_area_new();

  gtk_container_add(GTK_CONTAINER(window), glArea);
  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_show(glArea);
  gtk_widget_set_vexpand(glArea, TRUE);
  gtk_widget_set_hexpand(glArea, TRUE);
  g_signal_connect(glArea, "realize", G_CALLBACK(onGLAreaRealize), NULL);
  g_signal_connect(glArea, "render", G_CALLBACK(onGLAreaRender), NULL);
}

void onGLAreaRealize(GtkGLArea *self, gint width, gint height, gpointer data) {
  GLfloat triangleVertices[] = { 0.0, 0.8, -0.8, -0.8, 0.8, -0.8 };
  const char *attributeName = "coord2d";
  GLint compileOK = GL_FALSE;
  GLint linkOK = GL_FALSE;

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  glDisableVertexAttribArray(0);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(fs, 1, &fsSource, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compileOK);

  if(!compileOK) {
    GLint logLength;
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
      gchar *log = g_malloc(logLength);
      glGetShaderInfoLog(fs, logLength, NULL, log);
      g_printerr("[GtkGLArea::realize] Fragment Shader error: %s\n", log);
      g_free(log);
    }

    return;
  }

  glShaderSource(vs, 1, &vsSource, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compileOK);

  if(!compileOK) {
    GLint logLength;
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
      gchar *log = g_malloc(logLength);
      glGetShaderInfoLog(vs, logLength, NULL, log);
      g_printerr("[GtkGLArea::realize] Vertex Shader error: %s\n", log);
      g_free(log);
    }

    return;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &linkOK);

  if(!linkOK) {
    GLint logLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
      gchar *log = g_malloc(logLength);
      glGetProgramInfoLog(program, logLength, NULL, log);
      g_printerr("[GtkGLArea::realize] Program link error: %s\n", log);
      g_free(log);
    }

    return;
  }

  attributeCoord2D = glGetAttribLocation(program, attributeName);

  if(attributeCoord2D == -1) {
    g_printerr("[GtkGLArea::realize] Could not bind attribute %s\n", attributeName);
    return;
  }
}

gboolean onGLAreaRender(GtkGLArea *self, GdkGLContext *context, gpointer data) {
  g_print("[GtkGLArea::render] Called\n");
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(program);
  glBindVertexArray (vao);
  glEnableVertexAttribArray(attributeCoord2D);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(attributeCoord2D, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attributeCoord2D);

  return TRUE;
}