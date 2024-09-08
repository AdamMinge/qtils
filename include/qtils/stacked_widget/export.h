#ifndef UTILS_STACKED_WIDGET_EXPORT_H
#define UTILS_STACKED_WIDGET_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(STACKED_WIDGET_EXPORTS)
#define STACKED_WIDGET_API QTILS_API_EXPORT
#else
#define STACKED_WIDGET_API QTILS_API_IMPORT
#endif

#endif  // UTILS_STACKED_WIDGET_EXPORT_H
