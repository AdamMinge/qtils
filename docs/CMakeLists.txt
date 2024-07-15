# ----------------------------------------------------------------------- #
# -------------------------- Set CMake version -------------------------- #
# ----------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# ----------------------------------------------------------------------- #
# ------------------ Generate and install documentation ----------------- #
# ----------------------------------------------------------------------- #
if(QTILS_BUILD_DOCUMENTATION)
  find_package(Doxygen REQUIRED)
  set(DOXYGEN_IN ${QTILS_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  add_custom_target(
    docs_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/
          DESTINATION ${CMAKE_INSTALL_PREFIX}/docs)
endif()
# ----------------------------------------------------------------------- #
