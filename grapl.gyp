{
  'includes':
  [
    'test/tests.gyp',
  ],
  'targets':
  [
    {
      'target_name': 'libgrapl',
	  'defines': [
	    'GLEW_STATIC',
        'SPS_STANDALONE',
        'MOZ_ENABLE_PROFILER_SPS',
	  ],
      'sources':
      [
        'lib/base/io/Path.cpp',
        'lib/gfx/gfxShader.cpp',
        'lib/gfx/mesh/gfxMesh.cc',
        'lib/gfx/mesh/gfxMesh.h',
        'lib/GL/glew.c',

        'lib/GL/glew.h',
        'lib/GL/glxew.h',
        'lib/GL/wglew.h',
        'lib/base/Error.h',
        'lib/base/ErrorList.h',
        'lib/base/Likely.h',
        'lib/base/Logging.h',
        'lib/base/telemetry.h',
        'lib/base/memory.h',
        'lib/base/memory/system_malloc.cc',
        'lib/base/memory/system_malloc.h',

        'lib/base/io/Path.h',

        'lib/math/vector.cc',
        'lib/math/vector.h',
        'lib/math/precision.h',

      ],
      'dependencies':
      [
        'external/glfw-3.1.2/glfw.gyp:glfw',
        'external/libuv-1.7.5/uv.gyp:libuv',
        'external/mozprofiler/build.gyp:GeckoProfilerStatic'
      ],
      'direct_dependent_settings':
      {
        'include_dirs':
        [
          './external',
          './lib',
          './external/glfw-3.1.2/include',
          './external/libuv-1.7.5/include',
          './external/mozprofiler/src',
          './external/mozprofiler/third_party/mfbt/include',
          './external/mozprofiler/third_party/spidermonkey/include',
        ],
      },
      'type': 'static_library',
      'include_dirs':
      [
        './external',
        './lib',
        './external/glfw-3.1.2/include',
        './external/libuv-1.7.5/include',
        './external/mozprofiler/src',
      ],
    },
    {
      'target_name': 'graplengine',
	  'defines': [
	    'GLEW_STATIC',
        'SPS_STANDALONE',
        'MOZ_ENABLE_PROFILER_SPS'
	  ],
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
