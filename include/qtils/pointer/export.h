#ifndef UTILS_POINTER_EXPORT_H
#define UTILS_POINTER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(POINTER_EXPORTS)
#define POINTER_API QTILS_API_EXPORT
#else
#define POINTER_API QTILS_API_IMPORT
#endif

#endif  // UTILS_POINTER_EXPORT_H