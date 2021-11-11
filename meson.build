project('c-gtk3-examples', 'c')

deps = [ dependency('gtk+-3.0', required: true) ]

sources = [
  'GtkActionBar',
  'GtkApplication',
  'GtkApplicationWindow',
  'GtkBox',
  'GtkBuilder',
  'GtkButton',
  'GtkComboBox',
  'GtkComboBoxText',
  'GtkDialog',
  'GtkEntry',
  'GtkEntryCompletion',
  'GtkExpander',
  'GtkFileChooserButton',
  'GtkFileChooserDialog',
  'GtkGrid',
  'GtkHeaderBar',
  'GtkImage',
  'GtkInfoBar',
  'GtkLabel',
  'GtkMessageDialog',
  'GtkStack1',
  'GtkStack2',
  'GtkTreeView',
  'GtkWindow'
]

foreach src : sources
  name = src.replace('Gtk', '')
  executable(name, src + '.c', dependencies: deps)
endforeach