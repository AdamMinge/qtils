# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/container)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/container)

set(sources)

set(includes ${include_root}/export.h ${include_root}/hash.h
             ${include_root}/map.h)
# ----------------------------------------------------------------------- #
# ------------------------- Qt libraries configuration ------------------ #
# ----------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# ----------------------------------------------------------------------- #
# -------------------------- Find external libraries ---------------------#
# ----------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Core)
# ----------------------------------------------------------------------- #
# -------------------------- Create qtils shared lib -------------------- #
# ----------------------------------------------------------------------- #
qtils_add_module(container SOURCES ${sources} ${includes} DEPENDS Qt6::Core)

target_include_directories(
  container
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
