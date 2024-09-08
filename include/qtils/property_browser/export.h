#ifndef QTILS_PROPERTY_BROWSER_EXPORT_H
#define QTILS_PROPERTY_BROWSER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(PROPERTY_BROWSER_EXPORTS)
#define PROPERTY_BROWSER_API QTILS_API_EXPORT
#else
#define PROPERTY_BROWSER_API QTILS_API_IMPORT
#endif

#endif  // QTILS_PROPERTY_BROWSER_EXPORT_H
