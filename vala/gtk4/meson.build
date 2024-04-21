src = [
  'action-bar',
  'application-window',
  'application',
  'assistant',
  'box',
  'builder',
  'fixed',
  'header-bar',
  'label',
  'list-box',
  'window',
]

builder = configure_file(
  input: 'builder.vala.in',
  output: 'builder.vala',
  configuration: builderConf
)

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk4)
  else
    executable(name, name + '.vala', dependencies: gtk4)
  endif
endforeach