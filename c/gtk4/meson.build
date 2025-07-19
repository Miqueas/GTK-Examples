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
  'glarea',
  'grid-1',
  'grid-2',
  'grid-3',
  'header-bar',
  'image-1',
  'image-2',
  'label',
  'list-box',
  'stack-1',
  'stack-2',
  'text-view',
  'window',
]

builder = configure_file(
  input: 'builder.c.in',
  output: 'builder.c',
  configuration: builder_gtk4_ui
)

image1 = configure_file(
  input: 'image-1.c.in',
  output: 'image-1.c',
  configuration: image_conf
)

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk4)
  elif name == 'glarea'
    executable(name, name + '.c', dependencies: [ gtk4, epoxy ])
  elif name == 'image-1'
    executable(name, image1, dependencies: gtk4)
  else
    executable(name, name + '.c', dependencies: gtk4)
  endif
endforeach