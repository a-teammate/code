## This is the cmake file for the gluegen standalone tool.
## Its used for generating reflection boilerplate code and hence gets
## shipped precompiled as tool which is integrated in the build-process on every platform.
## If you still need to compile this generator e.g. for extending the tool for other needs,
## you need to edit the LLVM_DIR and the other marked stuff below.

cmake_minimum_required(VERSION 2.8.12)


# clang is a subproject of llvm
####################################### EDIT_HERE
####################################### EDIT_HERE

# Windows-note: Make sure all slashes are unix style! / instead of \ 

set(LLVM_DIR "E:/weitere-Dokumente/Software/llvm-3.8.0.src")

set(LLVM_LIB_DIR "E:/weitere-Dokumente/Git/llvm-precompiled-lib")

# If you followed the clang build tutorial step by step and also named your llvm build folder
# "build", then the lines below need no further adaption, but just LLVM_DIR above.
set(LLVM_GENERAL_INCLUDE_DIR  "${LLVM_DIR}/include")
set(CLANG_GENERAL_INCLUDE_DIR "${LLVM_DIR}/tools/clang/include")

# Path where your generated project files lay for the llvm suite.
set(LLVM_BUILD_INCLUDE_DIR  "${LLVM_DIR}/build/include")

# Path where your generated project files lay for the downloaded clang project.
set(CLANG_BUILD_INCLUDE_DIR "${LLVM_DIR}/build/tools/clang/include")

######################################## /EDIT_HERE
######################################## /EDIT_HERE


set(inexor_basedir "../..")
set(EXE_DIR "out") ## Must be defined before of add_app

# Error if paths aren't set well
get_filename_component(MAINDIR "${CMAKE_SOURCE_DIR}" REALPATH)  # Main inexor folder
get_filename_component(BINDIR "${CMAKE_BINARY_DIR}" REALPATH)   # Where it generates the projects into
if(${MAINDIR} STREQUAL ${BINDIR})
    message(FATAL_ERROR "Keep your directories clean, don't generate the project-files in the main directory! ${MAINDIR} ${BINDIR}")
endif()

# INSTALL_LOCALLY will surpress the installation into CMAKE_INSTALL_PREFIX which is by default some global system path.
option(INSTALL_LOCALLY "Install everything relative to this folder (${MAIN_DIR}), to not polute your global configuration." ON)

if(INSTALL_LOCALLY)
  set(CMAKE_INSTALL_PREFIX ${MAINDIR} CACHE PATH "" FORCE)
  message(STATUS "Local installation chosen. No files will move outside this folder (${MAINDIR}). .. ${CMAKE_INSTALL_PREFIX}")
endif()

list(INSERT CMAKE_INCLUDE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR} ${inexor_basedir})
list(INSERT CMAKE_LIBRARY_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR} ${LLVM_LIB_DIR})

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# First choice is Debug
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE INTERN "")
endif()

# Set a default toolchain file
string(TOLOWER "${CMAKE_GENERATOR}" GEN)
if(GEN MATCHES ".*visual studio.*")
  set(CMAKE_TOOLCHAIN_FILE ${inexor_basedir}/platform/vs.cmake)
elseif(GEN MATCHES ".*mingw.*" OR MINGW)
  set(CMAKE_TOOLCHAIN_FILE ${inexor_basedir}/platform/mingw.cmake)
else()
  set(CMAKE_TOOLCHAIN_FILE ${inexor_basedir}/platform/linux.cmake)
endif()
message(STATUS "Using Toolchain File ${CMAKE_TOOLCHAIN_FILE}")


#########
project(gluegen)

include(${inexor_basedir}/cmake/functions.cmake)
include(${inexor_basedir}/cmake/platform_detection.cmake)
include(${inexor_basedir}/cmake/compile_flags_and_defs.cmake)

declare_module(gluegen .)

find_libs(LLVM_LIBS LLVMCore LIB LIB LLVMOption LIB LLVMMC
 LIB LLVMSupport
 LIB LLVMMCParser
 LIB LLVMBitReader
 LIB clangAST
 LIB clangBasic
 LIB clangDriver
 LIB clangFormat
 LIB clangFrontend
 LIB clangTooling
 LIB clangSerialization
 LIB clangParse
 LIB clangSema
 LIB clangEdit
 LIB clangAnalysis
 LIB clangASTMatchers
 LIB clangToolingCore
 LIB clangRewrite
 LIB clangLex
)

find_path(Boost_INCLUDE_DIRS boost/regex.hpp)
#find_libs(Boost_LIBRARIES boost_program_options LIB boost_regex)
add_app(gluecodegenerator ${GLUEGEN_MODULE_SOURCES} CONSOLE_APP)

target_link_libs(gluecodegenerator ${Boost_LIBRARIES} ${LLVM_LIBS})

include_directories(${inexor_basedir} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS}
  ${LLVM_BUILD_INCLUDE_DIR}
  ${LLVM_GENERAL_INCLUDE_DIR}
  ${CLANG_BUILD_INCLUDE_DIR}
  ${CLANG_GENERAL_INCLUDE_DIR}
)


#RUN:
# __REFLECTION_PASS__
