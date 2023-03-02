# Lua GTK 3 Examples

This repository contains a set of examples of GTK 3 with Lua. Based on [this repository](https://github.com/gerito1/vala-gtk-examples)

## Requeriments

Lua 5.1, 5.2 or 5.3 is required, Lua 5.4 was not tested already. Additionally, this dependencies are necessary:

 * [lgi][lgi_repo]
 * `gobject-introspection >= 1.70`
 * `gtk3 >= 3.24`

## Building

The [meson file](meson.build) it's just to help you for check the dependencies (except for [lgi][lgi_repo], you need to install it if you don't have it), it actually does nothing with the source files.

## GTK API covered in this repo

Here is a list of the demostrated GTK API in these examples:

  * [ActionBar][ActionBar_API]
  * [Application][Application_API]
  * [ApplicationWindow][ApplicationWindow_API]
  * [Box][Box_API]
  * [Builder][Builder_API]
  * [Button][Button_API]
  * [ComboBox][ComboBox_API]
  * [ComboBoxText][ComboBoxText_API]
  * [CssProvider][CssProvider_API]
  * [Dialog][Dialog_API]
  * [Entry][Entry_API]
  * [EntryCompletion][EntryCompletion_API]
  * [Expander][Expander_API]
  * [FileChooserButton][FileChooserButton_API]
  * [FileChooserDialog][FileChooserDialog_API]
  * [Grid][Grid_API]
  * [HeaderBar][HeaderBar_API]
  * [Image][Image_API]
  * [InfoBar][InfoBar_API]
  * [Label][Label_API]
  * [ListBox][ListBox_API]
  * [Notebook][Notebook_API]
  * [Overlay][Overlay_API]
  * [Paned][Paned_API]
  * [Revealer][Revealer_API]
  * [ScrolledWindow][ScrolledWindow_API]
  * [Stack][Stack_API]
  * [Statusbar][Statusbar_API]
  * [Window][Window_API]

[lgi_repo]: https://github.com/pavouk/lgi
[ActionBar_API]: https://developer.gnome.org/gtk3/stable/GtkActionBar.html
[Application_API]: https://developer.gnome.org/gtk3/stable/GtkApplication.html
[ApplicationWindow_API]: https://developer.gnome.org/gtk3/stable/GtkApplicationWindow.html
[Box_API]: https://developer.gnome.org/gtk3/stable/GtkBox.html
[Builder_API]: https://developer.gnome.org/gtk3/stable/GtkBuilder.html
[Button_API]: https://developer.gnome.org/gtk3/stable/GtkButton.html
[ComboBox_API]: https://developer.gnome.org/gtk3/stable/GtkComboBox.html
[ComboBoxText_API]: https://developer.gnome.org/gtk3/stable/GtkComboBoxText.html
[CssProvider_API]: https://developer.gnome.org/gtk3/stable/GtkCssProvider.html
[Dialog_API]: https://developer.gnome.org/gtk3/stable/GtkDialog.html
[Entry_API]: https://developer.gnome.org/gtk3/stable/GtkEntry.html
[EntryCompletion_API]: https://developer.gnome.org/gtk3/stable/GtkEntryCompletion.html
[Expander_API]: https://developer.gnome.org/gtk3/stable/GtkExpander.html
[FileChooserButton_API]: https://developer.gnome.org/gtk3/stable/GtkFileChooserButton.html
[FileChooserDialog_API]: https://developer.gnome.org/gtk3/stable/GtkFileChooserDialog.html
[Grid_API]: https://developer.gnome.org/gtk3/stable/GtkGrid.html
[HeaderBar_API]: https://developer.gnome.org/gtk3/stable/GtkHeaderBar.html
[Image_API]: https://developer.gnome.org/gtk3/stable/GtkImage.html
[InfoBar_API]: https://developer.gnome.org/gtk3/stable/GtkInfoBar.html
[Label_API]: https://developer.gnome.org/gtk3/stable/GtkLabel.html
[ListBox_API]: https://developer.gnome.org/gtk3/stable/GtkListBox.html
[Notebook_API]: https://developer.gnome.org/gtk3/stable/GtkNotebook.html
[Overlay_API]: https://developer.gnome.org/gtk3/stable/GtkOverlay.html
[Paned_API]: https://developer.gnome.org/gtk3/stable/GtkPaned.html
[Revealer_API]: https://developer.gnome.org/gtk3/stable/GtkRevealer.html
[ScrolledWindow_API]: https://developer.gnome.org/gtk3/stable/GtkScrolledWindow.html
[Stack_API]: https://developer.gnome.org/gtk3/stable/GtkStack.html
[Statusbar_API]: https://developer.gnome.org/gtk3/stable/GtkStatusbar.html
[Window_API]: https://developer.gnome.org/gtk3/stable/GtkWindow.html