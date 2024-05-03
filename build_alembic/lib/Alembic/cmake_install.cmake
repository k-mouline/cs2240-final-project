# Install script for directory: /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/libAlembic.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libAlembic.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libAlembic.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libAlembic.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Alembic" TYPE FILE FILES
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AlembicConfig.cmake"
    "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AlembicConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Alembic/AlembicTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Alembic/AlembicTargets.cmake"
         "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/CMakeFiles/Export/lib/cmake/Alembic/AlembicTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Alembic/AlembicTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Alembic/AlembicTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Alembic" TYPE FILE FILES "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/CMakeFiles/Export/lib/cmake/Alembic/AlembicTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Alembic" TYPE FILE FILES "/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/CMakeFiles/Export/lib/cmake/Alembic/AlembicTargets-noconfig.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcCoreAbstract/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcCoreOgawa/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Abc/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcCoreFactory/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcCoreLayer/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcCollection/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcMaterial/cmake_install.cmake")
  include("/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Ogawa/cmake_install.cmake")

endif()

