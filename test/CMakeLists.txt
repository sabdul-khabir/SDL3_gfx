set(PROJECT_NAME TestGfx)

################################################################################
# Source groups
################################################################################
set(Sources
    "TestGfx.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Sources}
)

################################################################################
# Target
################################################################################
add_executable(TestGfx TestGfx.c)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE TestGfx)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
endif()

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
add_custom_command_if(
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMANDS
	COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMAND   $<CONFIG:Debug> copy /y "*.bmp" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\"
	COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMAND $<CONFIG:Release> copy /y "*.bmp" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\"
	COMMENT "Copy SDL3, SDL3_gfx DLLs as well as test data"
)

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"SDL3;"
	"SDL3_test;"
	"SDL3_gfx"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)

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
add_executable(testimagefilter testimagefilter.c)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE TestImageFilter)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
endif()

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
add_custom_command_if(
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMANDS
	COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMENT "Copy SDL3 and SDL3_gfx DLLs"
)

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"SDL3;"
	"SDL3_gfx"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)
set(PROJECT_NAME TestRotozoom)

################################################################################
# Source groups
################################################################################
set(Sources
    "testrotozoom.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Sources}
)

################################################################################
# Target
################################################################################
add_executable(testrotozoom testrotozoom.c)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE TestRotozoom)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
endif()

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
add_custom_command_if(
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMANDS
	COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMAND   $<CONFIG:Debug> copy /y ".\\sample*.bmp" "${OUTPUT_DIRECTORY}
	COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMAND $<CONFIG:Release> copy /y ".\\sample*.bmp" "${OUTPUT_DIRECTORY}
	COMMENT "Copy SDL3 and SDL3_gfx DLLs"
)

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"SDL3;"
	"SDL3_test;"
	"SDL3_gfx"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
target_link_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)

set(PROJECT_NAME TestFramerate)

################################################################################
# Source groups
################################################################################
set(Sources
    "testframerate.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Sources}
)

################################################################################
# Target
################################################################################
add_executable(testframerate testframerate.c)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE TestFramerate)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${TARGET_NAME}$ENV{TargetExt}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${TARGET_NAME}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        PDB_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
endif()

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
add_custom_command_if(
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMANDS
	COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3.dll"
	COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL3_gfx.dll"
	COMMENT "Copy SDL3 and SDL3_gfx DLLs"
)

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL3;"
        "SDL3_test;"
        "SDL3_gfx"
    )
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)

