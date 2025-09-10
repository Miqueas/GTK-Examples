src = [
  'about-dialog',
  'action-bar',
  'application-window',
  'application',
  'button',
]

foreach name : src
  executable(name, name + '.cpp',
    dependencies: gtkmm3,
    cpp_args: [ '-std=c++23' ],
  )
endforeach