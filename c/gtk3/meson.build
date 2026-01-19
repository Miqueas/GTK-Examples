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
  'event-box',
  'expander',
  'file-chooser-button',
  'file-chooser-dialog',
  'file-chooser-native',
  'file-chooser-widget',
  'fixed',
  'flow-box',
  'font-button',
  'font-chooser-dialog',
  'font-chooser-widget',
  'frame',
  'gesture-drag',
  'glarea',
  'grid-1',
  'grid-2',
  'grid-3',
  'header-bar',
  'image-1',
  'image-2',
  'info-bar',
  'label',
  'level-bar',
  'link-button',
  'list-box',
  'message-dialog',
  'notebook',
  'overlay',
  'paned',
  'popover',
  'progress-bar',
  'radio-button',
  'revealer',
  'scale-button',
  'scale',
  'scrolled-window',
  'stack-1',
  'stack-2',
  'text-view',
  'toggle-button',
  'toolbar',
  'tooltip',
  'tree-view',
  'window'
]

builder = configure_file(
  input: 'builder.c.in',
  output: 'builder.c',
  configuration: builder_gtk3_ui
)

css_provider = configure_file(
  input: 'css-provider.c.in',
  output: 'css-provider.c',
  configuration: css_conf
)

image1 = configure_file(
  input: 'image-1.c.in',
  output: 'image-1.c',
  configuration: image_conf
)

foreach name : src
  if name == 'builder'
    executable(name, builder,
      dependencies: gtk3,
      c_args: [ '-std=c11' ],
    )
  elif name == 'css-provider'
    executable(name, css_provider,
      dependencies: gtk3,
      c_args: [ '-std=c11' ],
    )
  elif name == 'glarea'
    executable(name, name + '.c',
      dependencies: [ gtk3, epoxy, m ],
      c_args: [ '-std=c11' ],
    )
  elif name == 'image-1'
    executable(name, image1,
      dependencies: gtk3,
      c_args: [ '-std=c11' ],
    )
  else
    executable(name, name + '.c',
      dependencies: gtk3,
      c_args: [ '-std=c11' ],
    )
  endif
endforeach