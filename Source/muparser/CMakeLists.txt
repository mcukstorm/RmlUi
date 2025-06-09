# Bump versions on release
set(MUPARSER_VERSION_MAJOR 2)
set(MUPARSER_VERSION_MINOR 3)
set(MUPARSER_VERSION_PATCH 5)
set(MUPARSER_VERSION ${MUPARSER_VERSION_MAJOR}.${MUPARSER_VERSION_MINOR}.${MUPARSER_VERSION_PATCH})

if(MSVC)
    add_compile_definitions(NOMINMAX)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

FILE(GLOB_RECURSE MUPARSER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp") #all .cpp
add_library(muparser ${MUPARSER_SOURCES})

# Use the headers in the build-tree or the installed ones
target_include_directories(muparser PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(muparser PUBLIC MUPARSER_STATIC)
add_definitions( -DMUPARSER_STATIC )

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(muparser PRIVATE _DEBUG)
endif ()


set_target_properties(muparser PROPERTIES
        VERSION ${MUPARSER_VERSION}
        SOVERSION ${MUPARSER_VERSION_MAJOR}
)

add_library(muparser::muparser ALIAS muparser)
