# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/dialog)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/dialog)

set(sources ${source_root}/dialog_with_toggle_view.cpp
            ${source_root}/extended_file_dialog.cpp)

set(includes
    ${include_root}/export.h ${include_root}/dialog_with_url_links.h
    ${include_root}/dialog_with_toggle_view.h
    ${include_root}/extended_file_dialog.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries -------------------- #
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# ----------------------------------------------------------------------- #
# -------------------------- Create qtils shared lib -------------------- #
# ----------------------------------------------------------------------- #
qtils_add_module(dialog SOURCES ${sources} ${includes} DEPENDS Qt6::Widgets)

target_include_directories(
  dialog
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
