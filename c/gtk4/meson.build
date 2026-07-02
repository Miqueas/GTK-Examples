src = [
  'action-bar',
  'application',
  'application-window',
  'box',
  'builder',
  'button',
  'column-view',
  'drop-down',
  'entry',
  'expander',
  'fixed',
  'flow-box',
  'glarea',
  'grid-1',
  'grid-2',
  'grid-3',
  'header-bar',
  'image-1',
  'image-2',
  'label',
  'list-box',
  'list-view',
  'stack-1',
  'stack-2',
  'text-view',
  'window',
]

foreach name : src
  if name == 'glarea'
    executable(name, name + '.c',
      dependencies: [ gtk4, epoxy, m ],
      c_args: [ '-std=c23' ],
    )
  else
    executable(name, name + '.c',
      dependencies: gtk4,
      c_args: [ '-std=c23' ],
    )
  endif
endforeach