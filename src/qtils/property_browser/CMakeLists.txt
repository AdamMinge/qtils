# ----------------------------------------------------------------------- #
# ---------------------------- Set CMake Version ------------------------ #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ---------------------------- Set files variable ------------------------#
# ----------------------------------------------------------------------- #
set(source_root ${QTILS_SOURCE_DIR}/src/qtils/property_browser)
set(include_root ${QTILS_SOURCE_DIR}/include/qtils/property_browser)

set(sources
    ${source_root}/button_property_browser.cpp
    ${source_root}/editor_factory.cpp
    ${source_root}/group_box_property_browser.cpp
    ${source_root}/property_browser.cpp
    ${source_root}/property_browser_utils.cpp
    ${source_root}/property_manager.cpp
    ${source_root}/tree_property_browser.cpp
    ${source_root}/variant_property.cpp
    ${source_root}/priv/property_browser_utils_p.h)

set(includes
    ${include_root}/export.h
    ${include_root}/button_property_browser.h
    ${include_root}/editor_factory.h
    ${include_root}/group_box_property_browser.h
    ${include_root}/property_browser.h
    ${include_root}/property_manager.h
    ${include_root}/variant_property.h
    ${include_root}/variant_property.h)
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
qtils_add_module(property_browser SOURCES ${sources} ${includes}
                 DEPENDS_PRIVATE Qt6::Widgets)

target_include_directories(
  property_browser
  PUBLIC $<BUILD_INTERFACE:${QTILS_SOURCE_DIR}/include/>
  INTERFACE $<INSTALL_INTERFACE:include>
  PRIVATE ${QTILS_SOURCE_DIR}/src/)
# ----------------------------------------------------------------------- #
