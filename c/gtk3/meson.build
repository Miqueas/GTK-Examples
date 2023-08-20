src = [
  'action-bar',
  'application',
  'application-window',
  'assistant',
  'box',
  'builder',
  'button',
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

image1 = configure_file(
  input: 'image-1.c.in',
  output: 'image-1.c',
  configuration: { 'imagePath': meson.current_source_dir() / 'logo.png' }
)

foreach name : src
  if name == 'image-1'
    executable(name, image1, dependencies: gtk3)
  else
    executable(name, name + '.c', dependencies: gtk3)
  endif
endforeach