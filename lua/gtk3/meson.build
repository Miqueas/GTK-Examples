message('Run the Lua examples by just using the Lua command from the project root directory')
message('Except for the following Lua examples that needs to be configured:')

configure_file(
  input: 'builder-1.lua.in',
  output: 'builder-1.lua',
  configuration: builder_gtk3_ui
)

configure_file(
  input: 'builder-2.lua.in',
  output: 'builder-2.lua',
  configuration: builder_gtk3_ui
)

configure_file(
  input: 'css-provider.lua.in',
  output: 'css-provider.lua',
  configuration: css_conf
)

configure_file(
  input: 'image-1.lua.in',
  output: 'image-1.lua',
  configuration: image_conf
)