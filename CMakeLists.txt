
SET(LIBRARY_SOURCES
    library/config.cpp
    library/log.cpp
    library/sleep.cpp

    library/bitmap/bitmap.cpp
    library/bitmap/colortools.cpp
    library/bitmap/lodepng.cpp

    library/noise/voronoi.cpp

    library/math/baseconv.cpp
    library/math/frustum.cpp
    library/math/matrix.cpp

    library/opengl/camera.cpp
    library/opengl/fbo.cpp
    library/opengl/input.cpp
    library/opengl/oglfont.cpp
    library/opengl/oglfont_shader.cpp
    library/opengl/opengl.cpp
    library/opengl/shader.cpp
    library/opengl/shader.cpp
    library/opengl/texture.cpp
    library/opengl/vao.cpp
    library/opengl/window.cpp

    library/timing/highperf.cpp
    library/timing/integrator.cpp
    library/timing/timer.cpp
  )

add_library(library STATIC ${LIBRARY_SOURCES})
