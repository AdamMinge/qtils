#ifndef UTILS_SERIALIZER_EXPORT_H
#define UTILS_SERIALIZER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(SERIALIZER_EXPORTS)
#define SERIALIZER_API QTILS_API_EXPORT
#else
#define SERIALIZER_API QTILS_API_IMPORT
#endif

#endif  // UTILS_SERIALIZER_EXPORT_H
