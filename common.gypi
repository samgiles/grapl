{
  'conditions': [
    [
      'OS=="mac"', {
        'libraries': [
          '-framework OpenGL -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo',
        ],
        # Annoying and weird way of settings flags for clang (it's gyp's fauly)
        'xcode_settings': {
          'OTHER_CFLAGS': [
            '-emit-llvm',
            '-fno-exceptions',
          ],
          'CLANG_CXX_LANGUAGE_STANDARD': 'c++14'
        },
      },
    ],
    [
      'OS=="win"', {
        'libraries': [
          'opengl32.lib',
        ],
        'defines': [
          'WIN32_LEAN_AND_MEAN',
          'VC_EXTRALEAN',
        ],
      },
    ],
  ],
}
