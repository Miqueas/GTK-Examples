src = [
  'action-bar',
  'application',
  'application-window',
  'assistant',
  'box',
  'builder',
  'button',
  'combo-box-text',
  'header-bar',
  'label',
  'list-box',
  'fixed',
  'flow-box',
  'window',
]

builder = configure_file(
  input: 'builder.vala.in',
  output: 'builder.vala',
  configuration: { 'builderPath': meson.project_source_root() / 'data' / 'builder.ui' }
)

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk3)
  else
    executable(name, name + '.vala', dependencies: gtk3)
  endif
endforeach