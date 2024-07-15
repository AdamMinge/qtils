# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ------------------------#
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/line_edit)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/line_edit)
set(resources_root ${QTILS_SOURCE_DIR}/resources/qtils/line_edit)

set(sources
    ${source_root}/line_edit_with_history.cpp
    ${source_root}/file_browser_line_edit.cpp
    ${source_root}/dir_browser_line_edit.cpp)

set(includes
    ${include_root}/export.h ${include_root}/line_edit_with_history.h
    ${include_root}/file_browser_line_edit.h
    ${include_root}/dir_browser_line_edit.h)

set(resources ${resources_root}/line_edit.qrc)
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
qtils_add_module(
  line_edit
  SOURCES
  ${sources}
  ${includes}
  ${resources}
  DEPENDS
  Qt6::Widgets
  DEPENDS_PRIVATE
  qtils::dialog)

target_include_directories(
  line_edit
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
