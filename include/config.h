/* -------------------------------------------------------------------------- */
#ifndef QTILS__CONFIG_H
#define QTILS__CONFIG_H
/* -------------------------------------------------------------------------- */
/* ---------------------------- Define QTILS_ version -----------------------
 */
/* -------------------------------------------------------------------------- */
// clang-format off

#define QTILS__VERSION_MAJOR 
#define QTILS__VERSION_MINOR 
#define QTILS__VERSION_PATCH 
#define QTILS__VERSION ..
#define QTILS__VERSION_STR ".."

// clang-format on
/* -------------------------------------------------------------------------- */
/* ----------------------- Identify the operating system -------------------- */
/* -------------------------------------------------------------------------- */
#if defined(_WIN32)
#define QTILS__OS_WINDOWS
#elif defined(__linux__)
#define QTILS__OS_LINUX
#else
#error This operating system is not supported by QTILS_ library
#endif
/* -------------------------------------------------------------------------- */
/* ------------------------ Define a portable debug macro ------------------- */
/* -------------------------------------------------------------------------- */
#if !defined(NDEBUG)
#define QTILS__DEBUG
#endif
/* -------------------------------------------------------------------------- */
/* -------------------- Define helpers to set items as deprecated ----------- */
/* -------------------------------------------------------------------------- */
#if !defined(QTILS__DEPRECATED_WARNINGS)
#define QTILS__DEPRECATED [[deprecated]]
#else
#define QTILS__DEPRECATED
#endif
/* -------------------------------------------------------------------------- */
#endif  // QTILS__CONFIG_H
/* -------------------------------------------------------------------------- */
