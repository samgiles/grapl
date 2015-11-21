{
  "conditions": [
    [
      "OS==\"mac\"", 
      {
        "libraries": [
          "-framework OpenGL -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo"
        ]
      }
    ], 
    [
      "OS==\"win\"", 
      {
        "defines": [
          "WIN32_LEAN_AND_MEAN", 
          "VC_EXTRALEAN"
        ], 
        "libraries": [
          "opengl32.lib"
        ]
      }
    ]
  ], 
  "targets": [
    {
      "dependencies": [
        "external/glfw-3.1.2/glfw.gyp:glfw"
      ], 
      "direct_dependent_settings": {
        "include_dirs": [
          "./external", 
          "./lib", 
          "./external/glfw-3.1.2/include"
        ]
      }, 
      "include_dirs": [
        "./external", 
        "./lib", 
        "./external/glfw-3.1.2/include"
      ], 
      "sources": [
        "lib/base/io/Path.cpp", 
        "lib/gfx/gfxShader.cpp", 
        "lib/GL/glew.c"
      ], 
      "target_name": "libgrapl", 
      "type": "static_library"
    }, 
    {
      "dependencies": [
        "libgrapl", 
        "external/glfw-3.1.2/glfw.gyp:glfw"
      ], 
      "include_dirs": [
        "src"
      ], 
      "sources": [
        "src/main.cpp"
      ], 
      "target_name": "graplengine", 
      "type": "executable"
    }
  ]
}