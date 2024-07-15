# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/action)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/action)

set(sources ${source_root}/action.cpp)

set(includes ${include_root}/export.h ${include_root}/action.h)
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
qtils_add_module(action SOURCES ${sources} ${includes} DEPENDS Qt6::Widgets)

target_include_directories(
  action
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
