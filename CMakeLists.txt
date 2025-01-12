#Sets the minimum required version of cmake for a project
cmake_minimum_required(VERSION 3.16.0)

# Set the project name
project(SDL3_gfx LANGUAGES C VERSION "1.0.0")

################################################################################
# Sub-projects
################################################################################
add_subdirectory(test)

################################################################################
# Options
################################################################################
option(BUILD_SHARED_LIBS "Build shared libraries (dll / so)" Off)
option(USE_MMX "use mmx assembly on x86" ON)
option(BUILD_TESTS "Build tests" Off)
################################################################################
# Source groups
################################################################################
set(Headers
    "SDL3_framerate.h"
    "SDL3_gfxPrimitives.h"
    "SDL3_gfxPrimitives_font.h"
    "SDL3_imageFilter.h"
    "SDL3_rotozoom.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "SDL3_framerate.c"
    "SDL3_gfxPrimitives.c"
    "SDL3_imageFilter.c"
    "SDL3_rotozoom.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
# Use BUILD_SHARED_LIBS to determine if the library is STATIC or SHARED
add_library(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SDL3_gfx)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()

################################################################################
# Include directories
################################################################################
# Include SDL3 include folder
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../SDL/include"
)


################################################################################
# Dependencies
################################################################################
# Include SDL3 as our only dependency
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "SDL3"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

# Set local of SDL3 library
target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)

