project('GTK-Examples', [ 'c', 'vala' ],
  version: '0.1.0',
  license: 'Zlib',
  meson_version: '>= 0.56.0'
)

gtk3 = dependency('gtk+-3.0', required: true)
gtk4 = dependency('gtk4', required: true)

subdir('c/gtk3')
subdir('c/gtk4')
subdir('vala/gtk3')
subdir('vala/gtk4')