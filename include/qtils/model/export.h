#ifndef UTILS_MODEL_EXPORT_H
#define UTILS_MODEL_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(MODEL_EXPORTS)
#define MODEL_API QTILS_API_EXPORT
#else
#define MODEL_API QTILS_API_IMPORT
#endif

#endif  // UTILS_MODEL_EXPORT_H
