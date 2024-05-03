# Install script for directory: /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Alembic/AbcGeom" TYPE FILE FILES
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/All.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Foundation.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/ArchiveBounds.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/IGeomBase.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OGeomBase.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/GeometryScope.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/SchemaInfoDeclarations.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OLight.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/ILight.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/FilmBackXformOp.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/CameraSample.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/ICamera.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OCamera.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Basis.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/CurveType.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/ICurves.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OCurves.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/FaceSetExclusivity.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OFaceSet.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/IFaceSet.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/ONuPatch.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/INuPatch.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OGeomParam.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/IGeomParam.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OPoints.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/IPoints.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OPolyMesh.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/IPolyMesh.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OSubD.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/ISubD.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Visibility.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/XformOp.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/XformSample.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/IXform.h"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/OXform.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests/cmake_install.cmake")

endif()

