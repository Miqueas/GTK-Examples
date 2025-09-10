project('GTK-Examples', [ 'c', 'vala', 'cpp' ],
  version: '0.1.0',
  license: 'Zlib',
  meson_version: '>= 0.56.0',
)

gtk3 = dependency('gtk+-3.0', required: true)
gtk4 = dependency('gtk4', required: true)
epoxy = dependency('epoxy', required: true)
gtkmm3 = dependency('gtkmm-3.0', required: true)
gtkmm4 = dependency('gtkmm-4.0', required: true)

gnome = import('gnome')
resources = gnome.compile_resources('resources', 'data/resources.xml',
  source_dir: 'data'
)

builder_gtk3_ui = { 'builderPath': meson.project_source_root() / 'data' / 'builder-gtk3.ui' }
builder_gtk4_ui = { 'builderPath': meson.project_source_root() / 'data' / 'builder-gtk4.ui' }
css_conf = { 'cssPath': meson.project_source_root() / 'data' / 'css-provider.css' }
image_conf = { 'imagePath': meson.project_source_root() / 'data' / 'grid-explained.png' }

subdir('c/gtk3')
subdir('c/gtk4')
subdir('cpp/gtk3/oop')
subdir('cpp/gtk3/procedural')
subdir('cpp/gtk4/oop')
subdir('cpp/gtk4/procedural')
subdir('lua/gtk3')
subdir('lua/gtk4')
subdir('vala/gtk3')
subdir('vala/gtk4')