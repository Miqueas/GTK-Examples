/*****************************************************************************
 * DashGL.com GTK GL-Area                                                    *
 * This file is in the public domain                                         *
 * Contributors: Benjamin Collins                                            *
 *****************************************************************************/

#include <gtk/gtk.h>
#include <GL/glew.h>

void onAppStartup(GApplication *self, gpointer data);
void onAppActivate(GApplication *self, gpointer data);
void onGLAreaRealize(GtkGLArea *self, gint width, gint height, gpointer data);
gboolean onGLAreaRender(GtkGLArea *self, GdkGLContext *context, gpointer data);

const gchar *appID = "io.github.Miqueas.GTK-Examples.C.Gtk4.GLArea";
const gchar *appTitle = "GtkApplicationWindow";

GLuint program, vao, vboTriangle;
GLint attributeCoord2D;

int main(int argc, char **argv) {
	GtkApplication *app = gtk_application_new(appID, 0);

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

  gtk_window_set_child(GTK_WINDOW(window), glArea);
  gtk_window_set_title(GTK_WINDOW(window), appTitle);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  gtk_widget_set_vexpand(glArea, TRUE);
	gtk_widget_set_hexpand(glArea, TRUE);
	g_signal_connect(glArea, "realize", G_CALLBACK(onGLAreaRealize), NULL);
	g_signal_connect(glArea, "render", G_CALLBACK(onGLAreaRender), NULL);
}

void onGLAreaRealize(GtkGLArea *self, gint width, gint height, gpointer data) {
  GLfloat triangleVertices[] = { 0.0, 0.8, -0.8, -0.8, 0.8, -0.8 };
  GLint compileOK = GL_FALSE;
  GLint linkOK = GL_FALSE;

  const char *vsSource =
  "#version 130\n" // OpenGL 3
  "attribute vec2 coord2d; \n"
  "void main (void) { \n"
  "   gl_Position = vec4(coord2d, 0.0, 1.0); \n"
  "}";

  const char *fsSource =
  "#version 130\n" // OpenGL 3
  "void main (void) {\n"
  "   gl_FragColor[0] = 1.0;\n"
  "   gl_FragColor[1] = 0.0;\n"
  "   gl_FragColor[2] = 0.0;\n"
  "}";

  const char *attributeName = "coord2d";

  g_print("[GtkGLArea::realize] Called\n");

	gtk_gl_area_make_current(self);
	
	if (gtk_gl_area_get_error (self) != NULL) {
		g_printerr("[GtkGLArea::realize] Unknown error\n");
		return;
	}

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	g_print("[GtkGLArea::realize] Renderer: %s\n", renderer);
	g_print("[GtkGLArea::realize] OpenGL version supported %s\n", version);

	gtk_gl_area_set_has_depth_buffer(self, TRUE);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

  glGenBuffers(1, &vboTriangle);
  glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);
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
    g_printerr("[GtkGLArea::realize] Error in fragment shader\n");
    return;
  }

  glShaderSource(vs, 1, &vsSource, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compileOK);

  if(!compileOK) {
    g_printerr("[GtkGLArea::realize] Error in vertex shader\n");
    return;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &linkOK);

  if(!linkOK) {
    g_printerr("[GtkGLArea::realize] Error when linking program\n");
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

  glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);
  glVertexAttribPointer(attributeCoord2D, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attributeCoord2D);

	return TRUE;
}