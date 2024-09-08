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
#error This operating system is not supported by QTILS library
#endif
/* -------------------------------------------------------------------------- */
/* ------------------------ Define a portable debug macro ------------------- */
/* -------------------------------------------------------------------------- */
#if !defined(NDEBUG)
#define QTILS_DEBUG
#endif
/* -------------------------------------------------------------------------- */
/* ----------------------- Define a export/import dll macro ----------------- */
/* -------------------------------------------------------------------------- */
#if !defined(QTILS_STATIC)

#if defined(QTILS_OS_WINDOWS)

#define QTILS_API_EXPORT __declspec(dllexport)
#define QTILS_API_IMPORT __declspec(dllimport)

#ifdef _MSC_VER

#pragma warning(disable : 4251)

#endif

#else

#define QTILS_API_EXPORT __attribute__((__visibility__("default")))
#define QTILS_API_IMPORT __attribute__((__visibility__("default")))

#endif

#else

#define QTILS_API_EXPORT
#define QTILS_API_IMPORT

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
