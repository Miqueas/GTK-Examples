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
precision mediump float;
void main(void) {
  gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}]]

local program, vao, vbo, attributeCoord2D

local function onGLAreaRealize(self)
  print('[Gtk.GLArea::realize] Called')
  self:make_current()

  local error = self:get_error()
  if error ~= nil then
    return print('[Gtk.GLArea::realize] Error:', error)
  end

  GL.init()

  local renderer = GL.get_string('renderer')
  local version = GL.get_string('version')
  print('[Gtk.GLArea::realize] Renderer:', renderer)
  print('[Gtk.GLArea::realize] Version:', version)

  self:set_has_depth_buffer(true)
  GL.clear_color(1.0, 1.0, 1.0, 1.0)

  program, _, _ = GL.make_program_s('vertex', vsSource, 'fragment', fsSource)

  attributeCoord2D = GL.get_attrib_location(program, 'coord2d')
  if attributeCoord2D == -1 then
    return print('[Gtk.GLArea::realize] Could not bind attribute coord2d')
  end

  vao = GL.new_vertex_array()
  GL.bind_vertex_array(vao)

  local triangleVertices = { 0.0, 0.8, -0.8, -0.8, 0.8, -0.8 }

  vbo = GL.new_buffer('array')
  GL.bind_buffer('array', vbo)
  GL.buffer_data('array', GL.pack('float', triangleVertices), 'static draw')

  GL.vertex_attrib_pointer(attributeCoord2D, 2, 'float', false, 0, 0)
  GL.enable_vertex_attrib_array(attributeCoord2D)

  GL.bind_vertex_array(0)
  GL.bind_buffer('array', 0)

  print('[Gtk.GLArea::realize] Setup complete')
end

local function onGLAreaRender(self)
  print('[Gtk.GLArea::render] Called')
  GL.clear('color', 'depth')

  if program == nil then return true end

  GL.use_program(program)
  GL.bind_vertex_array(vao)
  GL.draw_arrays('triangles', 0, 3)
  GL.bind_vertex_array(0)
  GL.use_program(0)

  return true
end

local function onAppStartup(self)
  local window = Gtk.ApplicationWindow { application = self }
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

local app = Gtk.Application { application_id = appID, flags = 0 }
app.on_activate = function (self) self.active_window:present() end
app.on_startup = onAppStartup

os.exit(app:run(arg), true)