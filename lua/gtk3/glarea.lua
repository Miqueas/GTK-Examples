local lgi = require('lgi')
local Gtk = lgi.require('Gtk', '3.0')
local GL = require('moongl')

local appID = 'io.github.Miqueas.GTK-Examples.Lua.Gtk3.GLArea'
local appTitle = 'Gtk.GLArea'

local vsSource = [[#version 100
attribute vec2 coord2d;
void main(void) {
  gl_Position = vec4(coord2d, 0.0, 1.0);
}]]

local fsSource = [[#version 100
void main(void) {
  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}]]

local program, vao, vbo, attributeCoord2D

local function onGLAreaRealize(self)
  local triangleVertices = { 0.0, 0.8, -0.8, -0.8, 0.8, -0.8 }
  local attributeName = 'coord2d'
  local compileOk = false
  local linkOk = false

  print('[Gtk.GLArea::realize] Called')
  self:make_current()

  if self:get_error() ~= nil then
    print('[Gtk.GLArea::realize] Unknown error')
    return
  end

  GL.init()

  local renderer = GL.get_string('renderer')
  local version = GL.get_string('version')

  print('[Gtk.GLArea::realize] Renderer:', renderer)
  print('[Gtk.GLArea::realize] Version:', version)

  self:set_has_depth_buffer(true)

  GL.clear_color(1.0, 1.0, 1.0, 1.0)

  vao = GL.new_vertex_array()
  GL.bind_vertex_array(vao)

  vbo = GL.new_buffer('array')
  GL.bind_buffer('array', vbo)
  GL.buffer_data('array', GL.pack('float', triangleVertices), 'static draw')
  GL.vertex_attrib_pointer(0, 2, 'float', false, 0, 0)
  GL.enable_vertex_attrib_array(0)
  GL.disable_vertex_attrib_array(0)

  local fs = GL.create_shader('fragment')
  local vs = GL.create_shader('vertex')

  GL.shader_source(fs, fsSource)
  GL.compile_shader(fs, true)

  GL.shader_source(vs, vsSource)
  GL.compile_shader(vs, true)

  program = GL.create_program()
  GL.attach_shader(program, fs)
  GL.attach_shader(program, vs)
  GL.link_program(program, true)

  attributeCoord2D = GL.get_attrib_location(program, attributeName)
  if attributeCoord2D == -1 then
    print('[Gtk.GLArea::realize] Could not bind attribute:', attributeName)
    return
  end
end

local function onGLAreaRender(self)
  print('[Gtk.GLArea::render] Called')

  GL.clear('color', 'depth')
  GL.use_program(program)
  GL.bind_vertex_array(vao)
  GL.enable_vertex_attrib_array(attributeCoord2D)
  GL.bind_buffer('array', vbo)
  GL.vertex_attrib_pointer(attributeCoord2D, 2, 'float', false, 0, 0)
  GL.draw_arrays('triangles', 0, 3)
  GL.disable_vertex_attrib_array(attributeCoord2D)
end

local function onAppStartup(self)
  local window = Gtk.ApplicationWindow { application = self, title = appTitle }
  local glArea = Gtk.GLArea {}

  window:add(glArea)
  window:set_title(appTitle)
  window:set_default_size(400, 400)

  glArea:show()
  glArea:set_vexpand(true)
  glArea:set_hexpand(true)
  glArea.on_realize = onGLAreaRealize
  glArea.on_render = onGLAreaRender
end

local app = Gtk.Application { application_id = appID }
app.on_activate = function (self) self.active_window:present() end
app.on_startup = onAppStartup

os.exit(app:run(arg), true)