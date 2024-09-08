#ifndef QTILS_DIALOG_EXPORT_H
#define QTILS_DIALOG_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(DIALOG_EXPORTS)
#define DIALOG_API QTILS_API_EXPORT
#else
#define DIALOG_API QTILS_API_IMPORT
#endif

#endif  // QTILS_DIALOG_EXPORT_H
