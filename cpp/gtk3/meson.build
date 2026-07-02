src = [
  'about-dialog.oop',
  'about-dialog.proc',
  'action-bar.oop',
  'action-bar.proc',
  'app-chooser-button.oop',
  'app-chooser-button.proc',
  'app-chooser-dialog.proc',
  'app-chooser-widget.proc',
  'application-window.oop',
  'application-window.proc',
  'application.oop',
  'application.proc',
  'button.oop',
  'button.proc',
]

foreach name : src
  executable(name, name + '.cpp',
    dependencies: gtkmm3,
    cpp_args: [ '-std=c++23' ],
    win_subsystem: 'windows'
  )
endforeach