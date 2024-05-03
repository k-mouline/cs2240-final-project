# Install script for directory: /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Alembic/Abc" TYPE FILE FILES
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/All.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/Base.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ErrorHandler.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/Foundation.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/Argument.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ArchiveInfo.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/IArchive.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/IArrayProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/IBaseProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ICompoundProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/IObject.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ISampleSelector.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/IScalarProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ISchema.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ISchemaObject.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ITypedArrayProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/ITypedScalarProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OArchive.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OArrayProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OBaseProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OCompoundProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OObject.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OScalarProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OSchema.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OSchemaObject.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OTypedArrayProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/OTypedScalarProperty.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/Reference.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/SourceName.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/TypedArraySample.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Abc/TypedPropertyTraits.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Abc/Tests/cmake_install.cmake")

endif()

