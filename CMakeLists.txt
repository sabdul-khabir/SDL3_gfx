#Sets the minimum required version of cmake for a project
cmake_minimum_required(VERSION 3.16.0)

# Set the project name
project(SDL3_gfx LANGUAGES C VERSION "1.0.1")
set(SDL_REQUIRED_VERSION 3.2.0)
string(REPLACE "." ";" SO_VERSION_COMPONENTS "${CMAKE_PROJECT_VERSION}")
list(GET SO_VERSION_COMPONENTS 0 SO_VERSION_MAJOR)

################################################################################
# Options
################################################################################
option(BUILD_TESTS "Build tests" Off)

################################################################################
# Source groups
################################################################################
# Assign list of header files to the variable 'Headers'
set(Headers
    "SDL3_framerate.h"
    "SDL3_gfxPrimitives.h"
    "SDL3_gfxPrimitives_font.h"
    "SDL3_imageFilter.h"
    "SDL3_rotozoom.h"
)

#Define a grouping for source files (for IDEs)
source_group("Headers" FILES ${Headers})

# Assign list of source files to the variable 'Sources'
set(Sources
    "SDL3_framerate.c"
    "SDL3_gfxPrimitives.c"
    "SDL3_imageFilter.c"
    "SDL3_rotozoom.c"
)

#Define a grouping for source files (for IDEs)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
# Build an static and a dynamic library.
if(NOT (CMAKE_SYSTEM_NAME STREQUAL "Emscripten"))
  add_library(${PROJECT_NAME}_Shared SHARED ${ALL_FILES})
endif()
add_library(${PROJECT_NAME}_Static STATIC ${ALL_FILES})

# Set 3 properties on the static target
set_target_properties(
    ${PROJECT_NAME}_Static PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}
  ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_NAME}_Static
  PUBLIC_HEADER "${Headers}"
)
if(NOT(CMAKE_SYSTEM_NAME STREQUAL "Emscripten"))
  set_target_properties(
      ${PROJECT_NAME}_Shared PROPERTIES
    VERSION "${CMAKE_PROJECT_VERSION}" SOVERSION "${SO_VERSION_MAJOR}"
    OUTPUT_NAME ${PROJECT_NAME}
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_NAME}_Shared
  )
endif()

################################################################################
# Include directories
################################################################################
# Specify include directories to use when compiling SDL3_gfx
# Include SDL3 include folder
if(NOT (CMAKE_SYSTEM_NAME STREQUAL "Emscripten"))
  target_include_directories(${PROJECT_NAME}_Shared PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../SDL/include"
  )
endif()

# Add the include directories of standard SDL3 for static library.
target_include_directories(${PROJECT_NAME}_Static PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../SDL/include"
)
################################################################################
# Dependencies
################################################################################

# In Emscripten there are only static libraries.
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  find_library(SDL3_LIB libSDL3.a)
else()
  find_library(SDL3_LIB SDL3)
endif()

# Specify libraries directories that we will link with SDL3_gfx.
# Static libraries don't need linking.
if(NOT(CMAKE_SYSTEM_NAME STREQUAL "Emscripten"))
  target_link_libraries(${PROJECT_NAME}_Shared PUBLIC ${SDL3_LIB})
endif()

# copy to default locations
if(NOT(CMAKE_SYSTEM_NAME STREQUAL "Emscripten"))
  install (TARGETS ${PROJECT_NAME}_Shared
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib/${PROJECT_NAME})
endif()
# Install headers following the convension of SDL3.
install (TARGETS ${PROJECT_NAME}_Static
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  PUBLIC_HEADER DESTINATION include/SDL3_gfx
)

################################################################################
# pkg-config
################################################################################
include( GNUInstallDirs )
configure_file(sdl3-gfx.pc.in sdl3-gfx.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/sdl3-gfx.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")


################################################################################
# Sub-projects
################################################################################
# build the test also
if(BUILD_TESTS AND NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  add_subdirectory(test)
endif()
