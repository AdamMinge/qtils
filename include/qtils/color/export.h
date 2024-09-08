#ifndef QTILS_COLOR_EXPORT_H
#define QTILS_COLOR_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(COLOR_EXPORTS)
#define COLOR_API QTILS_API_EXPORT
#else
#define COLOR_API QTILS_API_IMPORT
#endif

#endif  // QTILS_COLOR_EXPORT_H
