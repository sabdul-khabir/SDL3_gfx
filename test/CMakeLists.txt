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
add_executable(${PROJECT_NAME} ${ALL_FILES})

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
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od;
                /ZI
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-;
                /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-
            >
            /W3;
            /Zi;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib;
                /MACHINE:X86
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    endif()
endif()

################################################################################
# Post build events
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMANDS
        COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMAND   $<CONFIG:Debug> copy /y "*.bmp" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\"
        COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMAND $<CONFIG:Release> copy /y "*.bmp" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\"
        COMMENT "Copy SDL3, SDL3_gfx DLLs as well as test data"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL2;"
        "SDL2main;"
        "SDL2test;"
        "SDL2_gfx"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL3;"
        "SDL3_test;"
        "SDL3_gfx"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
endif()



























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
add_executable(${PROJECT_NAME} ${ALL_FILES})

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
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/include"
        ">"
        "$<$<CONFIG:Release>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
        ">"
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od;
                /ZI
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-;
                /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-
            >
            /W3;
            /Zi;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib;
                /MACHINE:X86
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    endif()
endif()

################################################################################
# Post build events
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMANDS
        COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMENT "Copy SDL3 and SDL3_gfx DLLs"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL2;"
        "SDL2main;"
        "SDL2_gfx"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL3;"
        "SDL3_gfx"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
endif()



























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
add_executable(${PROJECT_NAME} ${ALL_FILES})

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
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/include"
        ">"
        "$<$<CONFIG:Release>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
        ">"
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od;
                /ZI
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-;
                /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-
            >
            /W3;
            /Zi;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib;
                /MACHINE:X86
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    endif()
endif()

################################################################################
# Post build events
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMANDS
        COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMAND   $<CONFIG:Debug> copy /y ".\\sample*.bmp" "${OUTPUT_DIRECTORY}
        COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMAND $<CONFIG:Release> copy /y ".\\sample*.bmp" "${OUTPUT_DIRECTORY}
        COMMENT "Copy SDL3 and SDL3_gfx DLLs"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL2;"
        "SDL2main;"
        "SDL2test;"
        "SDL2_gfx"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL3;"
        "SDL3_test;"
        "SDL3_gfx"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
endif()



























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
add_executable(${PROJECT_NAME} ${ALL_FILES})

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
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/include"
        ">"
        "$<$<CONFIG:Release>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
        ">"
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_CRT_SECURE_NO_WARNINGS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_WINDOWS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od;
                /ZI
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-;
                /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Gm-;
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy-
            >
            /W3;
            /Zi;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib;
                /MACHINE:X86
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /NODEFAULTLIB:msvcrtd.lib
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /DYNAMICBASE:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS;
            /INCREMENTAL
        )
    endif()
endif()

################################################################################
# Post build events
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMANDS
        COMMAND   $<CONFIG:Debug> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND   $<CONFIG:Debug> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMAND $<CONFIG:Release> copy /y "..\\..\\SDL2-2.0.5\\VisualC\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2.dll"
        COMMAND $<CONFIG:Release> copy /y "..\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll" "${TARGET_NAME}\\${CMAKE_VS_PLATFORM_NAME}\\$<CONFIG>\\SDL2_gfx.dll"
        COMMENT "Copy SDL3 and SDL3_gfx DLLs"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3_gfx
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL2;"
        "SDL2main;"
        "SDL2test;"
        "SDL2_gfx"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL3;"
        "SDL3_test;"
        "SDL3_gfx"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl2gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2-2.0.5/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../sdl3gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL3_gfx/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL/VisualC/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
endif()

