#ifndef UTILS_ACTION_EXPORT_H
#define UTILS_ACTION_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(ACTION_EXPORTS)
#define ACTION_API Q_DECL_EXPORT
#else
#define ACTION_API Q_DECL_IMPORT
#endif

#endif  // UTILS_ACTION_EXPORT_H
