################################################################################
# TestGfx Project
################################################################################
set(PROJECT_NAME TestGfx)

# Set the right compiler linker flags for Emscripten.
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  link_directories("${EMSCRIPTEN_SYSROOT}/lib")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

################################################################################
# Source groups
################################################################################
set(Sources
    "TestGfx.c"
)
source_group("Sources" FILES ${Sources})

################################################################################
# Target
################################################################################
add_executable(TestGfx TestGfx.c)

################################################################################
# Target name
################################################################################

################################################################################
# Output directory
################################################################################


################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/..;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
)

################################################################################
# Post build events
################################################################################
# Copy the SDL3 dll, copy the SDL3_gfx dll, copy the bitmaps,

################################################################################
# Dependencies
################################################################################
# Link with other targets.
set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"SDL3;"
	"SDL3_test;"
	"SDL3_gfx_Static"
	"m"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

################################################################################
# TestImageFilter Project
################################################################################
set(PROJECT_NAME TestImageFilter)

################################################################################
# Source groups
################################################################################
set(Sources
    "testimagefilter.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Sources}
)

################################################################################
# Target
################################################################################
add_executable(TestImageFilter testimagefilter.c)

################################################################################
# Target name
################################################################################

################################################################################
# Output directory
################################################################################


################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME}  PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/..;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
)

################################################################################
# Post build events
################################################################################


################################################################################
# Dependencies
################################################################################
# Link with other targets.
set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"SDL3;"
	"SDL3_gfx_Static"
	"m"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

################################################################################
# TestRotozoom Project
################################################################################
set(PROJECT_NAME TestRotozoom)

################################################################################
# Source groups
################################################################################
set(Sources
    "testrotozoom.c"
)
source_group("Sources" FILES ${Sources})

################################################################################
# Target
################################################################################
add_executable(TestRotozoom testrotozoom.c)

################################################################################
# Target name
################################################################################

################################################################################
# Output directory
################################################################################


################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/..;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
)

################################################################################
# Post build events
################################################################################

################################################################################
# Dependencies
################################################################################
# Link with other targets.
set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"SDL3;"
	"SDL3_test;"
	"SDL3_gfx_Static"
	"m"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

################################################################################
# TestFramerate Project
################################################################################
set(PROJECT_NAME TestFramerate)

################################################################################
# Source groups
################################################################################
set(Sources
    "testframerate.c"
)
source_group("Sources" FILES ${Sources})

################################################################################
# Target
################################################################################
add_executable(TestFramerate testframerate.c)

################################################################################
# Target name
################################################################################

################################################################################
# Output directory
################################################################################


################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/..;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
)
################################################################################
# Post build events
################################################################################

################################################################################
# Dependencies
################################################################################
# Link with other targets.
set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL3;"
        "SDL3_test;"
        "SDL3_gfx_Static"
		"m"
    )
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

# Resource files to copy
set(TEST_ASSETS
	"sample2x2.bmp"
	"sample3x3.bmp"
	"sample8.bmp"
	"sample8-box.bmp"
	"sample16x16.bmp"
	"sample24.bmp"
	"sample24-box.bmp"
)
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  foreach(asset IN LISTS TEST_ASSETS)
    target_compile_options(TestImageFilter PRIVATE "--preload-file=${asset}")
    target_compile_options(TestRotozoom PRIVATE "--preload-file=${asset}")
  endforeach()
else()
  file(COPY ${TEST_ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
