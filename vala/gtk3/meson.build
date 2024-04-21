src = [
  'action-bar',
  'application',
  'application-window',
  'assistant',
  'box',
  'builder',
  'button',
  'combo-box-text',
  'dialog',
  'entry-completion',
  'entry',
  'header-bar',
  'label',
  'list-box',
  'fixed',
  'flow-box',
  'message-dialog',
  'template',
  'window',
]

builder = configure_file(
  input: 'builder.vala.in',
  output: 'builder.vala',
  configuration: builder_gtk3_ui
)

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk3)
  elif name == 'template'
    executable(name, [name + '.vala', resources], dependencies: gtk3)
  else
    executable(name, name + '.vala', dependencies: gtk3)
  endif
endforeach