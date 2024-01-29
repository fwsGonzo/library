option(LIBRARY_USE_GLFW_PACKAGE "" ON)
option(LIBRARY_USE_GLFW "Use GLFW for library features" ON)

if (LIBRARY_USE_GLFW AND LIBRARY_USE_GLFW_PACKAGE)
	find_package(glfw3 REQUIRED)
	find_package(GLEW REQUIRED)
endif()

add_subdirectory(inc/glm)

SET(LIBRARY_SOURCES
    library/config.cpp
    library/log.cpp
    library/sleep.cpp

    library/bitmap/bitmap.cpp
    library/bitmap/colortools.cpp
    library/bitmap/lodepng.cpp

    library/noise/cosnoise.cpp
    library/noise/gabor.c
    library/noise/multifractal.c
    library/noise/noise1234.c
    library/noise/sdnoise1234.c
    library/noise/simplex1234.c
    library/noise/srdnoise23.c
    library/noise/torusnoise.c
    library/noise/turbulence.c
    library/noise/voronoi.cpp
    library/noise/worley.c

    library/math/baseconv.cpp
    library/math/frustum.cpp
    library/math/matrix.cpp

    library/timing/integrator.cpp

    library/voxels/voxelizer.cpp
    library/voxels/voxelmodel.cpp
  )

if (LIBRARY_USE_GLFW)
	list(APPEND LIBRARY_SOURCES
		library/opengl/camera.cpp
		library/opengl/fbo.cpp
		library/opengl/input.cpp
		library/opengl/oglfont.cpp
		library/opengl/oglfont_shader.cpp
		library/opengl/opengl.cpp
		library/opengl/query.cpp
		library/opengl/shader.cpp
		library/opengl/shader.cpp
		library/opengl/texture.cpp
		library/opengl/texture_buffer.cpp
		library/opengl/window.cpp
		library/opengl/ubo.cpp
		library/opengl/vao.cpp
	)
endif()

add_library(library STATIC ${LIBRARY_SOURCES})
target_include_directories(library PUBLIC include inc)
target_link_libraries(library PUBLIC glm)

if (LIBRARY_USE_GLFW AND LIBRARY_USE_GLFW_PACKAGE)
target_include_directories(library PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(library PUBLIC glfw ${GLEW_LIBRARIES})
elseif (LIBRARY_USE_GLFW)
target_link_libraries(library PUBLIC glfw libglew_static)
endif()
