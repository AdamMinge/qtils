#ifndef QTILS_WIDGET_EXPORT_H
#define QTILS_WIDGET_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(WIDGET_EXPORTS)
#define WIDGET_API Q_DECL_EXPORT
#else
#define WIDGET_API Q_DECL_IMPORT
#endif

#endif  // QTILS_WIDGET_EXPORT_H
