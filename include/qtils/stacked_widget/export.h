#ifndef UTILS_STACKED_WIDGET_EXPORT_H
#define UTILS_STACKED_WIDGET_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(STACKED_WIDGET_EXPORTS)
#define STACKED_WIDGET_API Q_DECL_EXPORT
#else
#define STACKED_WIDGET_API Q_DECL_IMPORT
#endif

#endif  // UTILS_STACKED_WIDGET_EXPORT_H
