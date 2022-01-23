project('c-gtk3-examples', 'c')

deps = dependency('gtk+-3.0', required: true)

sources = [
  'GtkActionBar',
  'GtkApplication',
  'GtkApplicationWindow',
  'GtkAssistant',
  'GtkBox',
  'GtkBuilder',
  'GtkButton',
  'GtkComboBox',
  'GtkComboBoxText',
  'GtkDialog1',
  'GtkDialog2',
  'GtkEntry',
  'GtkEntryCompletion',
  'GtkExpander',
  'GtkFileChooserButton',
  'GtkFileChooserDialog',
  'GtkFlowBox',
  'GtkGrid1',
  'GtkGrid2',
  'GtkGrid3',
  'GtkHeaderBar',
  'GtkImage1',
  'GtkImage2',
  'GtkInfoBar',
  'GtkLabel',
  'GtkListBox',
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