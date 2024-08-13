# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/widget)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/widget)
set(uis_root ${QTILS_SOURCE_DIR}/uis/qtils/widget)

set(sources
    ${source_root}/name_and_path_filler.cpp
    ${source_root}/shortcut_selector.cpp ${source_root}/color_picker.cpp)

set(includes ${include_root}/export.h ${include_root}/name_and_path_filler.h
             ${include_root}/shortcut_selector.h ${include_root}/color_picker.h)

set(uis ${uis_root}/name_and_path_filler.ui)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${uis_root})
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create qtils shared lib -------------------- #
# ----------------------------------------------------------------------- #
qtils_add_module(
  widget
  SOURCES
  ${sources}
  ${includes}
  ${uis}
  DEPENDS
  Qt6::Widgets)

target_include_directories(
  widget
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
