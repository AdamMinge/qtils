# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ------------------------#
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/view)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/view)

set(includes
    ${include_root}/export.h ${include_root}/concept.h
    ${include_root}/unselectable_view.h
    ${include_root}/mouse_over_selectable_view.h)
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
qtils_add_headers_only_module(view SOURCES ${includes} DEPENDS Qt6::Widgets)

target_include_directories(view INTERFACE $<INSTALL_INTERFACE:include>)
# ----------------------------------------------------------------------- #
