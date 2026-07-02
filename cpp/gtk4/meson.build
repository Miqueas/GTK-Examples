src = [
  'about-dialog.oop',
  'about-dialog.proc',
  'action-bar.oop',
  'action-bar.proc',
  'application-window.oop',
  'application-window.proc',
  'application.oop',
  'application.proc',
  'button.oop',
  'button.proc',
  'column-view.oop',
  'column-view.proc',
]

foreach name : src
  executable(name, name + '.cpp',
    dependencies: gtkmm4,
    cpp_args: [ '-std=c++23' ],
    win_subsystem: 'windows'
  )
endforeach