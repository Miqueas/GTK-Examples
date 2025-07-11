src = [
  'about-dialog-1',
  'about-dialog-2',
  'action-bar',
  'app-chooser-button',
  'app-chooser-dialog',
  'app-chooser-widget',
  'application-window',
  'application',
  'aspect-frame',
  'assistant',
  'box',
  'builder',
  'button-box',
  'button',
  'calendar',
  'check-button',
  'check-menu-item',
  'clipboard',
  'color-button',
  'color-chooser-dialog',
  'color-chooser-widget',
  'combo-box-text',
  'combo-box',
  'css-provider',
  'dialog-1',
  'dialog-2',
  'drawing-area',
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

css_provider = configure_file(
  input: 'css-provider.vala.in',
  output: 'css-provider.vala',
  configuration: css_conf
)

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk3)
  elif name == 'css-provider'
    executable(name, css_provider, dependencies: gtk3)
  elif name == 'template'
    executable(name, [name + '.vala', resources], dependencies: gtk3)
  else
    executable(name, name + '.vala', dependencies: gtk3)
  endif
endforeach