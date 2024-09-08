# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ------------------------#
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/file_system)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/file_system)

set(sources ${source_root}/file_system_watcher.cpp
            ${source_root}/file_system_proxy_model.cpp)

set(includes
    ${include_root}/../config.h ${include_root}/export.h
    ${include_root}/file_system_watcher.h
    ${include_root}/file_system_proxy_model.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration -------------------#
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries ---------------------#
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create qtils shared lib ---------------------#
# ----------------------------------------------------------------------- #
qtils_add_module(file_system SOURCES ${sources} ${includes} DEPENDS
                 Qt6::Widgets)

target_include_directories(
  file_system
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
