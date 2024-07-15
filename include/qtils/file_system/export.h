#ifndef QTILS_FILE_SYSTEM_EXPORT_H
#define QTILS_FILE_SYSTEM_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(FILE_SYSTEM_EXPORTS)
#define FILE_SYSTEM_API Q_DECL_EXPORT
#else
#define FILE_SYSTEM_API Q_DECL_IMPORT
#endif

#endif  // QTILS_FILE_SYSTEM_EXPORT_H
