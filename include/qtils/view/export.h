#ifndef UTILS_VIEW_EXPORT_H
#define UTILS_VIEW_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(VIEW_EXPORTS)
#define VIEW_API QTILS_API_EXPORT
#else
#define VIEW_API QTILS_API_IMPORT
#endif

#endif  // UTILS_VIEW_EXPORT_H
