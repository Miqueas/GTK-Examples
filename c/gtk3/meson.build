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
  'clipboard',
  'color-button',
  'combo-box',
  'combo-box-text',
  'dialog-1',
  'dialog-2',
  'entry',
  'entry-completion',
  'expander',
  'file-chooser-button',
  'file-chooser-dialog',
  'fixed',
  'flow-box',
  'grid-1',
  'grid-2',
  'grid-3',
  'header-bar',
  'image-1',
  'image-2',
  'info-bar',
  'label',
  'list-box',
  'message-dialog',
  'stack-1',
  'stack-2',
  'text-view',
  'tree-view',
  'window'
]

builder = configure_file(
  input: 'builder.c.in',
  output: 'builder.c',
  configuration: builder_gtk3_ui
)

image1 = configure_file(
  input: 'image-1.c.in',
  output: 'image-1.c',
  configuration: image_conf
)

if build_machine.system() == 'linux'
  executable('glarea', 'glarea.c', dependencies: [ gtk3, glew ])
endif

foreach name : src
  if name == 'builder'
    executable(name, builder, dependencies: gtk3)
  elif name == 'image-1'
    executable(name, image1, dependencies: gtk3)
  else
    executable(name, name + '.c', dependencies: gtk3)
  endif
endforeach