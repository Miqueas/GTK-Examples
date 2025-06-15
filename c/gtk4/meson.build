src = [
  'action-bar',
  'application',
  'application-window',
  'box',
  'builder',
  'button',
  'drop-down',
  'entry',
  'expander',
  'fixed',
  'flow-box',
  'header-bar',
  'label',
  'window',
]

builder = configure_file(
  input: 'builder.c.in',
  output: 'builder.c',
  configuration: builder_gtk4_ui
)

if build_machine.system() == 'linux'
  executable('glarea', 'glarea.c', dependencies: [ gtk4, glew ])
endif

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk4)
  else
    executable(name, name + '.c', dependencies: gtk4)
  endif
endforeach