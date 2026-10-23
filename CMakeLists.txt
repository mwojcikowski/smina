cmake_minimum_required(VERSION 3.15)

# Handle CMake 4.x policy for FindBoost
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

# Auto-detect vcpkg installed dependencies on Windows if no toolchain was explicitly passed
if(WIN32)
    if(EXISTS "C:/vcpkg/installed/x64-windows")
        list(APPEND CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows")
        set(BOOST_ROOT "C:/vcpkg/installed/x64-windows" CACHE PATH "Boost root directory")
        set(Boost_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include" CACHE PATH "Boost include directory")
        set(BOOST_LIBRARYDIR "C:/vcpkg/installed/x64-windows/lib" CACHE PATH "Boost library directory")
    endif()
endif()

project(smina CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization and compiler options
if(MSVC)
    add_compile_options(/O2 /GL /EHsc /bigobj /W3)
    add_definitions(
        -D_CRT_SECURE_NO_WARNINGS
        -D_CRT_NONSTDC_NO_DEPRECATE
        -DWIN32
        -D_WIN32
        -DNOMINMAX
        -DBOOST_TIMER_ENABLE_DEPRECATED
    )
    # Match runtime linking
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
else()
    add_compile_options(-O3 -Wall)
    # Check if native arch is supported
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
    if(COMPILER_SUPPORTS_MARCH_NATIVE)
        add_compile_options(-march=native)
    endif()
endif()

# Find Boost
find_package(Boost REQUIRED COMPONENTS
    program_options
    filesystem
    thread
    system
    iostreams
    regex
    serialization
    date_time
    timer
    chrono
)

# Find ZLIB
find_package(ZLIB REQUIRED)

# Find OpenBabel
# Allow user to specify OPENBABEL_DIR or search common paths
find_path(OPENBABEL_INCLUDE_DIR
    NAMES openbabel/mol.h
    PATHS
        ${OPENBABEL_DIR}/include/openbabel3
        ${OPENBABEL_DIR}/include/openbabel-2.0
        ${OPENBABEL_DIR}/include
        "${CMAKE_CURRENT_SOURCE_DIR}/../openbabel-install/include/openbabel3"
        "${CMAKE_CURRENT_SOURCE_DIR}/../openbabel-install/include"
        "C:/Program Files/OpenBabel-2.4.1/include"
        "C:/OpenBabel-2.4.1/include"
        /usr/include/openbabel3
        /usr/include/openbabel-2.0
        /usr/local/include/openbabel3
        /usr/local/include/openbabel-2.0
        /ucrt64/include/openbabel3
        /ucrt64/include/openbabel-2.0
        /mingw64/include/openbabel3
        /mingw64/include/openbabel-2.0
    PATH_SUFFIXES
        openbabel3
        openbabel-2.0
        openbabel
)

find_library(OPENBABEL_LIBRARY
    NAMES openbabel-3 openbabel openbabel-2 libopenbabel
    PATHS
        ${OPENBABEL_DIR}/lib
        ${OPENBABEL_DIR}/bin
        "${CMAKE_CURRENT_SOURCE_DIR}/../openbabel-install/bin"
        "${CMAKE_CURRENT_SOURCE_DIR}/../openbabel-install/lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/../openbabel-build/src/Release"
        "C:/Program Files/OpenBabel-2.4.1/bin"
        "C:/Program Files/OpenBabel-2.4.1/lib"
        "C:/OpenBabel-2.4.1/lib"
        /usr/lib
        /usr/local/lib
        /ucrt64/lib
        /mingw64/lib
)

if(NOT OPENBABEL_INCLUDE_DIR OR NOT OPENBABEL_LIBRARY)
    message(WARNING "OpenBabel 2.x not found automatically. Set -DOPENBABEL_DIR=<path> or -DOPENBABEL_INCLUDE_DIR=<path> and -DOPENBABEL_LIBRARY=<path>")
else()
    message(STATUS "Found OpenBabel include: ${OPENBABEL_INCLUDE_DIR}")
    message(STATUS "Found OpenBabel library: ${OPENBABEL_LIBRARY}")
endif()

# Find Eigen3
find_package(Eigen3 CONFIG QUIET)
if(TARGET Eigen3::Eigen)
    get_target_property(EIGEN_INCLUDE_DIR Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "Found Eigen3 target Eigen3::Eigen: ${EIGEN_INCLUDE_DIR}")
elseif(Eigen3_FOUND)
    message(STATUS "Found Eigen3: ${EIGEN3_INCLUDE_DIR}")
    set(EIGEN_INCLUDE_DIR ${EIGEN3_INCLUDE_DIR})
elseif(EXISTS "C:/vcpkg/installed/x64-windows/include/eigen3")
    set(EIGEN_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include/eigen3")
else()
    set(EIGEN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/eigen)
endif()

# Platform-specific link libraries
set(PLATFORM_LIBS "")
if(WIN32)
    list(APPEND PLATFORM_LIBS ws2_32 mswsock)
endif()

# Include directories
set(COMMON_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/CommandLine2
    ${EIGEN_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/eigen
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
    ${OPENBABEL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIRS}
)

# Core smina library source files
set(SMINA_LIB_SOURCES
    src/lib/builtinscoring.cpp
    src/lib/cache.cpp
    src/lib/coords.cpp
    src/lib/custom_terms.cpp
    src/lib/everything.cpp
    src/lib/flexinfo.cpp
    src/lib/grid.cpp
    src/lib/szv_grid.cpp
    src/lib/model.cpp
    src/lib/monte_carlo.cpp
    src/lib/mutate.cpp
    src/lib/my_pid.cpp
    src/lib/naive_non_cache.cpp
    src/lib/non_cache.cpp
    src/lib/obmolopener.cpp
    src/lib/parallel_mc.cpp
    src/lib/parse_pdbqt.cpp
    src/lib/pdb.cpp
    src/lib/quasi_newton.cpp
    src/lib/quaternion.cpp
    src/lib/random.cpp
    src/lib/ssd.cpp
    src/lib/terms.cpp
    src/lib/weighted_terms.cpp
    src/lib/molgetter.cpp
    src/lib/result_info.cpp
    src/lib/PDBQTUtilities.cpp
    src/lib/SminaConverter.cpp
)

add_library(libsmina STATIC ${SMINA_LIB_SOURCES})
target_include_directories(libsmina PUBLIC ${COMMON_INCLUDES})
target_link_libraries(libsmina PUBLIC
    ${Boost_LIBRARIES}
    ${OPENBABEL_LIBRARY}
    ${ZLIB_LIBRARIES}
    ${PLATFORM_LIBS}
)

# 1. Main executable: smina
add_executable(smina src/main/main.cpp)
target_include_directories(smina PRIVATE ${COMMON_INCLUDES})
target_link_libraries(smina PRIVATE libsmina)

# Automatically copy openbabel DLL next to executables on Windows
if(WIN32)
    get_filename_component(OPENBABEL_LIB_DIR "${OPENBABEL_LIBRARY}" DIRECTORY)
    find_file(OPENBABEL_DLL
        NAMES openbabel-3.dll openbabel-2.dll openbabel.dll libopenbabel.dll
        PATHS
            "${OPENBABEL_LIB_DIR}"
            "${OPENBABEL_LIB_DIR}/../bin"
            "${OPENBABEL_DIR}/bin"
            "${OPENBABEL_DIR}/bin/Release"
            "${CMAKE_CURRENT_SOURCE_DIR}/../openbabel-install/bin"
            "${CMAKE_CURRENT_SOURCE_DIR}/../openbabel-build/bin/Release"
    )
    if(OPENBABEL_DLL)
        message(STATUS "Found OpenBabel DLL: ${OPENBABEL_DLL}")
        get_filename_component(OPENBABEL_BIN_DIR "${OPENBABEL_DLL}" DIRECTORY)
        add_custom_command(TARGET smina POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${OPENBABEL_DLL}"
                "$<TARGET_FILE_DIR:smina>"
            COMMENT "Copying OpenBabel DLL to executable directory"
        )
        file(GLOB OBF_PLUGINS "${OPENBABEL_BIN_DIR}/*.obf")
        foreach(plugin ${OBF_PLUGINS})
            add_custom_command(TARGET smina POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${plugin}"
                    "$<TARGET_FILE_DIR:smina>"
            )
        endforeach()
        if(EXISTS "${OPENBABEL_BIN_DIR}/data")
            add_custom_command(TARGET smina POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${OPENBABEL_BIN_DIR}/data"
                    "$<TARGET_FILE_DIR:smina>/data"
            )
        endif()
    endif()
endif()

# 2. tosmina converter
add_executable(tosmina
    src/tosmina/tosmina.cpp
    src/lib/CommandLine2/CommandLine.cpp
)
target_include_directories(tosmina PRIVATE ${COMMON_INCLUDES})
target_link_libraries(tosmina PRIVATE libsmina)

# 3. fromsmina converter
add_executable(fromsmina
    src/fromsmina/fromsmina.cpp
    src/lib/CommandLine2/CommandLine.cpp
)
target_include_directories(fromsmina PRIVATE ${COMMON_INCLUDES})
target_link_libraries(fromsmina PRIVATE libsmina)

# 4. Minimization server (optional)
option(BUILD_SERVER "Build minimization server daemon" OFF)
if(BUILD_SERVER)
    add_executable(server
        src/server/server.cpp
        src/lib/CommandLine2/CommandLine.cpp
        src/server/MinimizationQuery.cpp
        src/server/QueryManager.cpp
    )
    target_include_directories(server PRIVATE ${COMMON_INCLUDES})
    target_link_libraries(server PRIVATE libsmina)
    install(TARGETS server RUNTIME DESTINATION bin)
endif()

# Install targets
install(TARGETS smina tosmina fromsmina libsmina
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
