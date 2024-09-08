# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/delegate)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/delegate)

set(sources ${source_root}/icon_check_delegate.cpp
            ${source_root}/conditional_bold_delegate.cpp)

set(includes
    ${include_root}/../config.h ${include_root}/export.h
    ${include_root}/icon_check_delegate.h
    ${include_root}/conditional_bold_delegate.h)
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
qtils_add_module(
  delegate
  SOURCES
  ${sources}
  ${includes}
  DEPENDS
  Qt6::Widgets
  DEPENDS_PRIVATE
  qtils::dpi)

target_include_directories(
  delegate
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
