#ifndef QTILS_FILE_SYSTEM_EXPORT_H
#define QTILS_FILE_SYSTEM_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(FILE_SYSTEM_EXPORTS)
#define FILE_SYSTEM_API QTILS_API_EXPORT
#else
#define FILE_SYSTEM_API QTILS_API_IMPORT
#endif

#endif  // QTILS_FILE_SYSTEM_EXPORT_H
