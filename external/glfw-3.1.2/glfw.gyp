{
  "includes": [],
  "target_defaults": {},
  "targets": [
    {
      "conditions": [
        [
          "OS==\"mac\"",
          {
            "defines": [
              "_GLFW_COCOA",
              "_GLFW_NSGL",
              "_GLFW_USE_OPENGL",
              "_GLFW_USE_CHDIR",
              "_GLFW_USE_MENUBAR",
              "_GLFW_USE_RETINA"
            ],
            "sources": [
              "src/cocoa_init.m",
              "src/nsgl_context.m",
              "src/cocoa_monitor.m",
              "src/cocoa_window.m",
              "src/iokit_joystick.m",
              "src/mach_time.c",
              "src/posix_tls.c"
            ],
            "libraries": [
              "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo"
            ],
            "direct_dependent_settings": {
              "libraries": [
                "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo"
              ]
            }
          }
        ],
        [
          "OS==\"win\"",
          {
            "defines": [
              "_GLFW_WIN32",
              "_GLFW_WGL",
              "_GLFW_USE_OPENGL"
            ],
            "sources": [
              "src/win32_init.c",
              "src/win32_monitor.c",
              "src/win32_time.c",
              "src/win32_tls.c",
              "src/win32_window.c",
              "src/winm_joystick.c"
            ],
            "libraries": [
              "opengl32.lib"
            ],
            "direct_dependent_settings": {
              "libraries": [
                "opengl32.lib"
              ]
            }
          }
        ]
      ],
      "defines": [
        "_GLFW_USE_OPENGL"
      ],
      "include_dirs": [
        "./external/glfw-3.1.2/include",
        "./external/glfw-3.1.2/deps",
        "./external/glfw-3.1.2"
      ],
      "sources": [
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/monitor.c",
        "src/posix_tls.c",
        "src/window.c",
      ],
      "target_name": "glfw",
      "type": "static_library"
    }
  ],
  "variables": {}
}
