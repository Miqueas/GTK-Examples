src = [
  'action-bar',
  'application-window',
  'application',
  'box',
  'builder',
  'css-provider',
  'fixed',
  'header-bar',
  'label',
  'list-box',
  'window',
]

builder = configure_file(
  input: 'builder.vala.in',
  output: 'builder.vala',
  configuration: builder_gtk4_ui
)

css_provider = configure_file(
  input: 'css-provider.vala.in',
  output: 'css-provider.vala',
  configuration: css_conf
)

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk4)
  elif name == 'css-provider'
    executable(name, css_provider, dependencies: gtk4)
  else
    executable(name, name + '.vala', dependencies: gtk4)
  endif
endforeach