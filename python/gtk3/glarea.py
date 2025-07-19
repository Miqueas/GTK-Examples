import gi, sys, numpy
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
from OpenGL.GL import *

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.GLArea"
appTitle = "Gtk.GLArea"
program = None
vao = None
vbo = None
attributeCoord2D = None

def onGLAreaRealize(self):
  global program, vao, vbo, attributeCoord2D

  triangleVertices = numpy.array(
    [ 0.0, 0.8, -0.8, -0.8, 0.8, -0.8 ],
    dtype = numpy.float32
  )
  attributeName = "coord2d"
  compileOk = GL_FALSE
  linkOk = GL_FALSE
  vsSource = """#version 130
  attribute vec2 coord2d;
  void main(void) {
    gl_Position = vec4(coord2d, 0.0, 1.0);
  }"""

  fsSource = """#version 130
  void main(void) {
    gl_FragColor[0] = 0.0;
    gl_FragColor[1] = 0.0;
    gl_FragColor[2] = 0.0;
  }"""

  print("[Gtk.GLArea::realize] Called")
  self.make_current()

  if self.get_error() is not None:
    print("[Gtk.GLArea::realize] Unknown error", file = sys.stderr)
    return

  renderer = glGetString(GL_RENDERER)
  version = glGetString(GL_VERSION)

  print(f"[Gtk.GLArea::realize] Renderer: {renderer.decode('utf-8')}")
  print(f"[Gtk.GLArea::realize] Version: {version.decode('utf-8')}")

  self.set_has_depth_buffer(True)

  glClearColor(1.0, 1.0, 1.0, 0.0)

  vao = glGenVertexArrays(1)
  glBindVertexArray(vao)

  vbo = glGenBuffers(1)
  glBindBuffer(GL_ARRAY_BUFFER, vbo)
  glBufferData(
    GL_ARRAY_BUFFER,
    triangleVertices.nbytes,
    triangleVertices,
    GL_STATIC_DRAW
  )

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, None)
  glEnableVertexAttribArray(0)
  glDisableVertexAttribArray(0)

  fs = glCreateShader(GL_FRAGMENT_SHADER)
  vs = glCreateShader(GL_VERTEX_SHADER)

  glShaderSource(fs, fsSource)
  glCompileShader(fs)
  compileOk = glGetShaderiv(fs, GL_COMPILE_STATUS)

  if not compileOk:
    print("[Gtk.GLArea::realize] Error in fragment shader", file = sys.stderr)
    return
  
  glShaderSource(vs, vsSource)
  glCompileShader(vs)
  compileOk = glGetShaderiv(vs, GL_COMPILE_STATUS)

  if not compileOk:
    print("[Gtk.GLArea::realize] Error in vertex shader", file = sys.stderr)
    return
  
  program = glCreateProgram()
  glAttachShader(program, vs)
  glAttachShader(program, fs)
  glLinkProgram(program)
  linkOk = glGetProgramiv(program, GL_LINK_STATUS)

  if not linkOk:
    print("[Gtk.GLArea::realize] Error when linking program", file = sys.stderr)
    return
  
  attributeCoord2D = glGetAttribLocation(program, attributeName)

  if attributeCoord2D == -1:
    print(
      f"[Gtk.GLArea::realize] Could not bind attribute {attributeName}",
      file = sys.stderr
    )
    return

def onGLAreaRender(self, context):
  global program, vao, vbo, attributeCoord2D

  print("[Gtk.GLArea::render] Called")

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
  glUseProgram(program)
  glBindVertexArray(vao)
  glEnableVertexAttribArray(attributeCoord2D)
  glBindBuffer(GL_ARRAY_BUFFER, vbo)
  glVertexAttribPointer(attributeCoord2D, 2, GL_FLOAT, GL_FALSE, 0, None)
  glDrawArrays(GL_TRIANGLES, 0, 3)
  glDisableVertexAttribArray(attributeCoord2D)

  return True

def onAppStartup(self):
  global appTitle

  window = Gtk.ApplicationWindow(application = self)
  glArea = Gtk.GLArea()

  window.add(glArea)
  window.set_title(appTitle)
  window.set_default_size(400, 400)

  glArea.show()
  glArea.set_vexpand(True)
  glArea.set_hexpand(True)
  glArea.connect("realize", onGLAreaRealize)
  glArea.connect("render", onGLAreaRender)

app = Gtk.Application(application_id = appID, flags = 0)
app.connect("activate", lambda self: self.get_active_window().present())
app.connect("startup", onAppStartup)

sys.exit(app.run(sys.argv))