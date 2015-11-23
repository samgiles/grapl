{
  'includes':
  [
    'test/tests.gyp',
  ],
  'targets':
  [
    {
      'target_name': 'libgrapl',
      'sources':
      [
        'lib/base/io/Path.cpp',
        'lib/gfx/gfxShader.cpp',
        'lib/GL/glew.c',

        'lib/GL/glew.h',
        'lib/GL/glxew.h',
        'lib/GL/wglew.h',
        'lib/base/Error.h',
        'lib/base/ErrorList.h',
        'lib/base/Likely.h',
        'lib/base/Logging.h',

        'lib/base/io/Path.h',
      ],
      'dependencies':
      [
        'external/glfw-3.1.2/glfw.gyp:glfw',
        'external/libuv-1.7.5/uv.gyp:libuv'
      ],
      'direct_dependent_settings':
      {
        'include_dirs':
        [
          './external',
          './lib',
          './external/glfw-3.1.2/include',
          './external/libuv-1.7.5/include',
        ],
      },
      'type': 'static_library',
      'include_dirs':
      [
        './external',
        './lib',
        './external/glfw-3.1.2/include',
        './external/libuv-1.7.5/include',
      ],
    },
    {
      'target_name': 'graplengine',
      'sources':
      [
        'src/main.cpp',
      ],
      'dependencies':
      [
        'libgrapl',
        'external/glfw-3.1.2/glfw.gyp:glfw',
      ],
      'type': 'executable',
      'include_dirs':
      [
        'src'
      ],
    }
  ],
}
