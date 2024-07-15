# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ----------------------- #
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/pointer)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/pointer)

set(sources)

set(includes ${include_root}/export.h ${include_root}/unique_ptr_cast.h
             ${include_root}/lazy_ptr.h)
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
qtils_add_module(pointer SOURCES ${sources} ${includes} DEPENDS Qt6::Core)

target_include_directories(
  pointer
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
