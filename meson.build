project('GTK-Examples', [ 'c', 'vala' ],
  version: '0.1.0',
  license: 'Zlib',
  meson_version: '>= 0.56.0'
)

# Allows using the 'with' keyword in Vala without warnings
add_project_arguments('--enable-experimental', language: 'vala')

gtk3 = dependency('gtk+-3.0', required: true)
gtk4 = dependency('gtk4', required: true)

gnome = import('gnome')
resources = gnome.compile_resources('resources', 'data/resources.xml', source_dir: 'data')

builderConf = { 'builderPath': meson.project_source_root() / 'data' / 'builder.ui' }
cssConf = { 'cssPath': meson.project_source_root() / 'data' / 'css-provider.css' }
imageConf = { 'imagePath': meson.project_source_root() / 'data' / 'grid-explained.png' }

subdir('c/gtk3')
subdir('c/gtk4')
subdir('lua/gtk3')
subdir('vala/gtk3')
subdir('vala/gtk4')