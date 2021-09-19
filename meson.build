project('c-gtk3-examples', 'c')

deps = [ dependency('gtk+-3.0') ]

sources = [
  'GtkActionBar.c',
  'GtkApplication.c',
  'GtkApplicationWindow.c',
  'GtkBox.c',
  'GtkBuilder.c',
  'GtkButton.c',
  'GtkComboBox.c',
  'GtkComboBoxText.c',
  'GtkDialog.c',
  'GtkEntry.c',
  'GtkEntryCompletion.c',
  'GtkExpander.c',
  'GtkFileChooserButton.c',
  'GtkFileChooserDialog.c',
  'GtkGrid.c',
  'GtkHeaderBar.c',
  'GtkImage.c',
  'GtkInfoBar.c',
  'GtkLabel.c',
  'GtkMessageDialog.c',
  'GtkStack1.c',
  'GtkStack2.c',
  'GtkTreeView.c',
  'GtkWindow.c'
]

foreach src : sources
  executable(src.replace('.c', ''), src, dependencies: deps)
endforeach