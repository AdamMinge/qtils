#ifndef QTILS_DELEGATE_EXPORT_H
#define QTILS_DELEGATE_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include "qtils/config.h"
/* -------------------------------------------------------------------------- */

#if defined(DELEGATE_EXPORTS)
#define DELEGATE_API QTILS_API_EXPORT
#else
#define DELEGATE_API QTILS_API_IMPORT
#endif

#endif  // QTILS_DELEGATE_EXPORT_H
