#ifndef QTILS_COLOR_EXPORT_H
#define QTILS_COLOR_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(COLOR_EXPORTS)
#define COLOR_API Q_DECL_EXPORT
#else
#define COLOR_API Q_DECL_IMPORT
#endif

#endif  // QTILS_COLOR_EXPORT_H
