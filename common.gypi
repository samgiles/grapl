{
  'variables': {
    'uv_library%': 'static_library',
  },
  'target_defaults': {
    'default_configuration': 'Release',
    'configurations': {
      'Debug' : {
        'defines': [ '_DEBUG' ],
        'cflags':  [ '-g', '-O0' ],
        # Annoying and weird way of settings flags for clang (it's gyp's fauly)
        'xcode_settings': {
          'GCC_OPTIMIZATION_LEVEL': '0',
          'OTHER_CFLAGS': [
            '-g',
            '-fno-exceptions',
          ]
        },
        'msvs_settings': {
          'RuntimeLibrary': 1,        # static debug
          'Optmization':    0,        # /0d no optimizations
          'MinimalRebuild': 'false',
          'BasicRuntimeChecks': 3     # /RTC1
        },
        'VCLinkerTool': {
          'LinkIncremental': 2 # Enable incremental linking
        }
      },
      'Release' : {
        'cflags+': [ '-O3' ],
        'xcode_settings': {
          'OTHER_CFLAGS': [
            '-O3',
            '-emit-llvm',
            '-fno-exceptions',
          ]
        },
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 0,                # static release
            'Optimization':   3,                # /0x full optimizations
            'FavorSizeOrSpeed': 1,              # /0t favour seped over size
            'InlineFunctionExpansion': 2,       # inline anything eligible
            'WholeProgramOptimization': 'true', # /GL, whole program optimization (required for LTCG)
            'OmitFramePointers': 'true',        # Frees up a register (ebp) for general purpose use
            'EnableFunctionLevelLinking': 'true',
            'EnableIntrinsicFunctions': 'true',
            'RuntimeTypeInfo': 'false',
            'AdditionalOptions': [
              '/MP' # Multip processing compilation
            ]
          },
          'VCLibrarianTool': {
            'AdditionalOptions': [
              '/LTCG' # Link time code generation
            ]
          },
          'VCLinkerTool': {
            'LinkTimeCodeGeneration': 1,
            'OptimizeReferences': 2,     # /OPT:REF
            'EnableCOMDATFolding': 2,    # /OPT:ICF
            'LinkIncremental': 1         # disable incremental linking
          }
        }
      }
    }
  },
  'conditions': [
    [
      'OS=="mac"', {
        'libraries': [
          '-framework OpenGL -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo',
        ],
        'xcode_settings': {
          'CLANG_CXX_LANGUAGE_STANDARD': 'c++14'
        },
      },
    ],
    [
      'OS=="win"', {
        'libraries': [
          'opengl32.lib',
		  'gdi32.lib',
		  'kernel32.lib'
        ],
        'defines': [
          'WIN32_LEAN_AND_MEAN',
          'VC_EXTRALEAN',
        ],
      },
    ],
  ],
}
