#ifndef QTILS_DPI_EXPORT_H
#define QTILS_DPI_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(DPI_EXPORTS)
#define DPI_API QTILS_API_EXPORT
#else
#define DPI_API QTILS_API_IMPORT
#endif

#endif  // QTILS_DPI_EXPORT_H
