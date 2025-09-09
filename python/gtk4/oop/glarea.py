import gi, sys
gi.require_version("Gtk", "4.0")
from gi.repository import Gtk
from OpenGL.GL import *
from OpenGL.GL import shaders
import numpy as np

class GLArea(Gtk.GLArea):
    VS_SOURCE = """#version 100
    attribute vec2 coord2d;
    void main(void) {
    gl_Position = vec4(coord2d, 0.0, 1.0);
    }"""

    FS_SOURCE = """#version 100
    precision mediump float;
    void main(void) {
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }"""

    program = None
    vao = None
    vbo = None
    attributeCoord2D = None

    def __init__(self):
        super().__init__()
        self.set_vexpand(True)
        self.set_hexpand(True)

    def do_realize(self):
        # Ensures chain-up
        Gtk.GLArea.do_realize(self)

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
            vs = shaders.compileShader(self.VS_SOURCE, GL_VERTEX_SHADER)
            fs = shaders.compileShader(self.FS_SOURCE, GL_FRAGMENT_SHADER)
            self.program = shaders.compileProgram(vs, fs)
        except Exception as e:
            return print(f"[Gtk.GLArea::realize] Shader compilation error: {e}", file=sys.stderr)

        self.attributeCoord2D = glGetAttribLocation(self.program, b"coord2d")
        if self.attributeCoord2D == -1:
            return print("[Gtk.GLArea::realize] Could not bind attribute coord2d", file=sys.stderr)

        self.vao = glGenVertexArrays(1)
        glBindVertexArray(self.vao)

        triangleVertices = np.array([0.0,  0.8, -0.8, -0.8, 0.8, -0.8], dtype=np.float32)

        self.vbo = glGenBuffers(1)
        glBindBuffer(GL_ARRAY_BUFFER, self.vbo)
        glBufferData(GL_ARRAY_BUFFER, triangleVertices.nbytes, triangleVertices, GL_STATIC_DRAW)

        glVertexAttribPointer(self.attributeCoord2D, 2, GL_FLOAT, GL_FALSE, 0, None)
        glEnableVertexAttribArray(self.attributeCoord2D)

        glBindVertexArray(0)
        glBindBuffer(GL_ARRAY_BUFFER, 0)

        print("[Gtk.GLArea::realize] Setup complete")

    def do_render(self, _):
        print("[Gtk.GLArea::render] Called")
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        if self.program is None:
            return True

        glUseProgram(self.program)
        glBindVertexArray(self.vao)
        glDrawArrays(GL_TRIANGLES, 0, 3)
        glBindVertexArray(0)
        glUseProgram(0)

        return True

class App(Gtk.Application):
    APP_ID = "io.github.Miqueas.GTK-Examples.Python.Gtk4.OOP.GLArea"
    APP_TITLE = "Gtk.GLArea"

    def __init__(self):
        super().__init__(application_id = self.APP_ID)

    def do_activate(self):
        window = self.get_active_window()
        if window: window.present()

    def do_startup(self):
        # Ensures chain-up
        Gtk.Application.do_startup(self)

        window = Gtk.ApplicationWindow(application = self)
        window.set_child(GLArea())
        window.set_title(self.APP_TITLE)
        window.set_default_size(400, 400)

if __name__ == "__main__":
    sys.exit(App().run(sys.argv))