project('GTK-Examples', [ 'c', 'vala' ],
  version: '0.1.0',
  license: 'Zlib',
  meson_version: '>= 0.56.0',
)

# Allows using the 'with' keyword in Vala without warnings
add_project_arguments('--enable-experimental', language: 'vala')

gtk3 = dependency('gtk+-3.0', required: true)
gtk4 = dependency('gtk4', required: true)

if build_machine.system() == 'linux'
  glew = dependency('glew', required: true)
else
  message('Skipping glew dependency on non-linux systems')
endif


gnome = import('gnome')
resources = gnome.compile_resources('resources', 'data/resources.xml', source_dir: 'data')

builder_gtk3_ui = { 'builderPath': meson.project_source_root() / 'data' / 'builder-gtk3.ui' }
builder_gtk4_ui = { 'builderPath': meson.project_source_root() / 'data' / 'builder-gtk4.ui' }
css_conf = { 'cssPath': meson.project_source_root() / 'data' / 'css-provider.css' }
image_conf = { 'imagePath': meson.project_source_root() / 'data' / 'grid-explained.png' }

subdir('c/gtk3')
subdir('c/gtk4')
subdir('lua/gtk3')
subdir('lua/gtk4')
subdir('vala/gtk3')
subdir('vala/gtk4')