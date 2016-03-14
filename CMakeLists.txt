
# Copyright Louis Dionne 2015
# Modified Work Copyright Barrett Adair 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.0)
project(callable_traits CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
enable_testing()

# Perform checks to make sure we support the current compiler
include(CheckCxxCompilerSupport)

if(callable_traits_CXX_STD)
else()
  # Defaults to C++14 if not set:
  set(callable_traits_CXX_STD 14) 
endif()

set (CMAKE_CXX_STANDARD ${callable_traits_CXX_STD})

# Setting up CMake options and compiler flags (more flags can be set on a per-target basis or in subdirectories)

option(callable_traits_ENABLE_WERROR   "Fail and stop if a warning is triggered." OFF)

include(CheckCXXCompilerFlag)
macro(callable_traits_append_flag testname flag)
    check_cxx_compiler_flag(${flag} ${testname})
    if (${testname})
        add_compile_options(${flag})
    endif()
endmacro()

if (callable_traits_ENABLE_WERROR)
    callable_traits_append_flag(callable_traits_HAS_WERROR -Werror)
    callable_traits_append_flag(callable_traits_HAS_WX -WX)
endif()

callable_traits_append_flag(callable_traits_HAS_FTEMPLATE_BACKTRACE_LIMIT  -ftemplate-backtrace-limit=0)
callable_traits_append_flag(callable_traits_HAS_PEDANTIC                   -pedantic)
callable_traits_append_flag(callable_traits_HAS_STDCXX1Y                   -std=c++1y)
callable_traits_append_flag(callable_traits_HAS_QUNUSED_ARGUMENTS          -Qunused-arguments)
callable_traits_append_flag(callable_traits_HAS_W                          -W)
callable_traits_append_flag(callable_traits_HAS_WALL                       -Wall)
callable_traits_append_flag(callable_traits_HAS_WEXTRA                     -Wextra)
callable_traits_append_flag(callable_traits_HAS_WNO_UNUSED_LOCAL_TYPEDEFS  -Wno-unused-local-typedefs)
callable_traits_append_flag(callable_traits_HAS_WWRITE_STRINGS             -Wwrite-strings)

#find_package(Boost 1.59)
#if (Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#else()
#    message(WARNING
#        "The Boost library headers were not found; targets depending "
#        "on Boost won't be available.")
#endif()
#
#find_package(Doxygen)
##find_package(Meta)
#find_package(PythonInterp 2.7)
#find_package(Ruby 2.1)

##############################################################################
# callable_traits_target_name_for(<output variable> <source file> [ext])
# Returns the target name associated to a source file. If the path of the
# source file relative from the root of callable_traits is `path/to/source/file.ext`,
# the target name associated to it will be `path.to.source.file`.
#
# The extension of the file should be specified as a last argument. If no
# extension is specified, the `.cpp` extension is assumed.
##############################################################################

function(callable_traits_target_name_for out file)
    if (NOT ARGV2)
        set(_extension ".cpp")
    else()
        set(_extension "${ARGV2}")
    endif()

    file(RELATIVE_PATH _relative ${callable_traits_SOURCE_DIR} ${file})
    string(REPLACE "${_extension}" "" _name ${_relative})
    string(REGEX REPLACE "/" "." _name ${_name})
    set(${out} "${_name}" PARENT_SCOPE)
endfunction()

##############################################################################
# callable_traits_add_test(<name> <command> [<arg>...])
# Creates a test called `name`, which runs the given `command` with the given args.
##############################################################################

function(callable_traits_add_test name)
    if (callable_traits_ENABLE_MEMCHECK)
        add_test(${name} ${Valgrind_EXECUTABLE} --leak-check=full --error-exitcode=1 ${ARGN})
    else()
        add_test(${name} ${ARGN})
    endif()
endfunction()

##############################################################################
# Setup the `check` target to build and then run all the tests and examples.
##############################################################################

add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Build and then run all the tests and examples.")

add_subdirectory(example)
add_subdirectory(test)

##############################################################################
# Setup the 'install' target.
# This copies the whole content of include/ to ${CMAKE_INSTALL_PREFIX}.
##############################################################################

install(DIRECTORY include/boost DESTINATION include
        PATTERN ".DS_Store" EXCLUDE)
