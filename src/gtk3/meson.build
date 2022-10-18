project('c-gtk-examples', 'c')

deps = dependency('gtk+-3.0', required: true)

sources = [
  'ActionBar',
  'Application',
  'ApplicationWindow',
  'Assistant',
  'Box',
  'Builder',
  'Button',
  'ComboBox',
  'ComboBoxText',
  'Dialog1',
  'Dialog2',
  'Entry',
  'EntryCompletion',
  'Expander',
  'FileChooserButton',
  'FileChooserDialog',
  'Fixed',
  'FlowBox',
  'Grid1',
  'Grid2',
  'Grid3',
  'HeaderBar',
  'Image1',
  'Image2',
  'InfoBar',
  'Label',
  'ListBox',
  'MessageDialog',
  'Stack1',
  'Stack2',
  'TextView',
  'TreeView',
  'Window'
]

foreach src : sources
  executable(src, src + '.c', dependencies: deps)
endforeach