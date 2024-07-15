#ifndef QTILS_DPI_EXPORT_H
#define QTILS_DPI_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(DPI_EXPORTS)
#define DPI_API Q_DECL_EXPORT
#else
#define DPI_API Q_DECL_IMPORT
#endif

#endif  // QTILS_DPI_EXPORT_H
