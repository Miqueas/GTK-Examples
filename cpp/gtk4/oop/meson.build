src = [
  'about-dialog',
  'action-bar',
  'application-window',
  'application',
  'button',
  'column-view',
]

foreach name : src
  executable(name, name + '.cpp',
    dependencies: gtkmm4,
    cpp_args: [ '-std=c++23' ],
    win_subsystem: 'windows'
  )
endforeach