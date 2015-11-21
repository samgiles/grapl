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
      "include_dirs": [
        "./external", 
        "./src", 
        "./external/glfw-3.1.2/include"
      ], 
      "sources": [
        "src/main.cpp", 
        "src/base/io/Path.cpp", 
        "src/gfx/gfxShader.cpp", 
        "src/GL/glew.c"
      ], 
      "target_name": "grapl", 
      "type": "executable"
    }
  ]
}