project('c-gtk-examples', 'c')

deps = dependency('gtk4', required: true)

sources = [
  'Application',
  'ApplicationWindow',
  'HeaderBar',
  'Label',
  'Box',
  'Window'
]

foreach src : sources
  executable(src, src + '.c', dependencies: deps)
endforeach