/* -------------------------------------------------------------------------- */
#ifndef QTILS_CONFIG_H
#define QTILS_CONFIG_H
/* -------------------------------------------------------------------------- */
/* ---------------------------- Define QTILS_ version -----------------------
 */
/* -------------------------------------------------------------------------- */
// clang-format off

#define QTILS_VERSION_MAJOR 0
#define QTILS_VERSION_MINOR 1
#define QTILS_VERSION_PATCH 0
#define QTILS_VERSION 0.1.0
#define QTILS_VERSION_STR "0.1.0"

// clang-format on
/* -------------------------------------------------------------------------- */
/* ----------------------- Identify the operating system -------------------- */
/* -------------------------------------------------------------------------- */
#if defined(_WIN32)
#define QTILS_OS_WINDOWS
#elif defined(__linux__)
#define QTILS_OS_LINUX
#else
#error This operating system is not supported by QTILS_ library
#endif
/* -------------------------------------------------------------------------- */
/* ------------------------ Define a portable debug macro ------------------- */
/* -------------------------------------------------------------------------- */
#if !defined(NDEBUG)
#define QTILS_DEBUG
#endif
/* -------------------------------------------------------------------------- */
/* -------------------- Define helpers to set items as deprecated ----------- */
/* -------------------------------------------------------------------------- */
#if !defined(QTILS_DEPRECATED_WARNINGS)
#define QTILS_DEPRECATED [[deprecated]]
#else
#define QTILS_DEPRECATED
#endif
/* -------------------------------------------------------------------------- */
#endif  // QTILS_CONFIG_H
/* -------------------------------------------------------------------------- */
