#ifndef QTILS_CONTAINER_EXPORT_H
#define QTILS_CONTAINER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(CONTAINER_EXPORTS)
#define CONTAINER_API Q_DECL_EXPORT
#else
#define CONTAINER_API Q_DECL_IMPORT
#endif

#endif  // QTILS_CONTAINER_EXPORT_H
