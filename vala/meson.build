project('Vala-GTK-Examples', [ 'vala', 'c' ],
  version: '0.1.0',
  license: 'Zlib',
  meson_version: '>= 0.56.0',
  default_options: [ 'warning_level=2' ]
)

gtk3 = dependency('gtk+-3.0', required: true)
gtk4 = dependency('gtk4', required: true)

subdir('gtk3')
subdir('gtk4')