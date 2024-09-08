#ifndef QTILS_WIDGET_EXPORT_H
#define QTILS_WIDGET_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(WIDGET_EXPORTS)
#define WIDGET_API QTILS_API_EXPORT
#else
#define WIDGET_API QTILS_API_IMPORT
#endif

#endif  // QTILS_WIDGET_EXPORT_H
