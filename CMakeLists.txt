project(SDL3_gfx)
cmake_minimum_required(VERSION 2.8)
add_subdirectory(test)

set(${project}_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_framerate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_gfxPrimitives.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_imageFilter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_rotozoom.c
)

set(${project}_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_framerate.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_gfxPrimitives.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_gfxPrimitives_font.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_imageFilter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3_rotozoom.h
)

add_library(${project} STATIC ${${project}_SOURCES} ${${project}_HEADERS} )
