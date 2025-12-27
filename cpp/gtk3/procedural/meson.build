src = [
  'about-dialog',
  'action-bar',
  'app-chooser-button',
  'app-chooser-dialog',
  'app-chooser-widget',
  'application-window',
  'application',
  'button',
]

foreach name : src
  executable(name, name + '.cpp',
    dependencies: gtkmm3,
    cpp_args: [ '-std=c++23' ],
    win_subsystem: 'windows'
  )
endforeach