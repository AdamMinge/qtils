#ifndef QTILS_CONTAINER_EXPORT_H
#define QTILS_CONTAINER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(CONTAINER_EXPORTS)
#define CONTAINER_API QTILS_API_EXPORT
#else
#define CONTAINER_API QTILS_API_IMPORT
#endif

#endif  // QTILS_CONTAINER_EXPORT_H
