src = [
  'application',
  'window',
  'application-window',
  'header-bar',
  'label',
  'box',
]

executable('glarea', 'glarea.c', dependencies: [ gtk4, glew ])

foreach name : src
  executable(name, name + '.c', dependencies: gtk4)
endforeach