src = [
  'application',
  'window',
  'application-window',
  'header-bar',
  'label',
  'box',
]

if build_machine.system() == 'linux'
  executable('glarea', 'glarea.c', dependencies: [ gtk4, glew ])
endif

foreach name : src
  executable(name, name + '.c', dependencies: gtk4)
endforeach