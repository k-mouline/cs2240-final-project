# Install script for directory: /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcMaterial

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Alembic/AbcMaterial" TYPE FILE FILES
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcMaterial/All.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcMaterial/SchemaInfoDeclarations.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcMaterial/OMaterial.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcMaterial/IMaterial.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcMaterial/MaterialFlatten.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcMaterial/MaterialAssignment.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcMaterial/Tests/cmake_install.cmake")

endif()

