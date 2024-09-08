#ifndef UTILS_ACTION_EXPORT_H
#define UTILS_ACTION_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(ACTION_EXPORTS)
#define ACTION_API QTILS_API_EXPORT
#else
#define ACTION_API QTILS_API_IMPORT
#endif

#endif  // UTILS_ACTION_EXPORT_H
