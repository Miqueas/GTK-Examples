import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
from OpenGL.GL import *
from OpenGL.GL import shaders
import numpy as np

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.GLArea"
appTitle = "Gtk.GLArea"

vsSource = """#version 100
attribute vec2 coord2d;
void main(void) {
  gl_Position = vec4(coord2d, 0.0, 1.0);
}"""

fsSource = """#version 100
precision mediump float;
void main(void) {
  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}"""

program = None
vao = None
vbo = None
attributeCoord2D = None

def onGLAreaRealize(self):
    global vsSource, fsSource, program, vao, vbo, attributeCoord2D

    print("[Gtk.GLArea::realize] Called")
    self.make_current()

    error = self.get_error()
    if error is not None:
        return print(f"[Gtk.GLArea::realize] Error: {error}", file=sys.stderr)

    renderer = glGetString(GL_RENDERER)
    version = glGetString(GL_VERSION)
    print(f"[Gtk.GLArea::realize] Renderer: {renderer.decode('utf-8')}")
    print(f"[Gtk.GLArea::realize] Version: {version.decode('utf-8')}")

    self.set_has_depth_buffer(True)
    glClearColor(1.0, 1.0, 1.0, 1.0)

    try:
        vs = shaders.compileShader(vsSource, GL_VERTEX_SHADER)
        fs = shaders.compileShader(fsSource, GL_FRAGMENT_SHADER)
        program = shaders.compileProgram(vs, fs)
    except Exception as e:
        return print(f"[Gtk.GLArea::realize] Shader compilation error: {e}", file=sys.stderr)

    attributeCoord2D = glGetAttribLocation(program, b"coord2d")
    if attributeCoord2D == -1:
        return print("[Gtk.GLArea::realize] Could not bind attribute coord2d", file=sys.stderr)

    vao = glGenVertexArrays(1)
    glBindVertexArray(vao)

    triangleVertices = np.array([0.0,  0.8, -0.8, -0.8, 0.8, -0.8], dtype=np.float32)

    vbo = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, vbo)
    glBufferData(GL_ARRAY_BUFFER, triangleVertices.nbytes, triangleVertices, GL_STATIC_DRAW)

    glVertexAttribPointer(attributeCoord2D, 2, GL_FLOAT, GL_FALSE, 0, None)
    glEnableVertexAttribArray(attributeCoord2D)

    glBindVertexArray(0)
    glBindBuffer(GL_ARRAY_BUFFER, 0)

    print("[Gtk.GLArea::realize] Setup complete")

def onGLAreaRender(self, context):
    global program, vao

    print("[Gtk.GLArea::render] Called")
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    if program is None: return True

    glUseProgram(program)
    glBindVertexArray(vao)
    glDrawArrays(GL_TRIANGLES, 0, 3)
    glBindVertexArray(0)
    glUseProgram(0)

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