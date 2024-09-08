#ifndef UTILS_LINE_EDIT_EXPORT_H
#define UTILS_LINE_EDIT_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(LINE_EDIT_EXPORTS)
#define LINE_EDIT_API QTILS_API_EXPORT
#else
#define LINE_EDIT_API QTILS_API_IMPORT
#endif

#endif  // UTILS_LINE_EDIT_EXPORT_H
