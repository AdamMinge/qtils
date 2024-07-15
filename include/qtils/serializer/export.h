#ifndef UTILS_SERIALIZER_EXPORT_H
#define UTILS_SERIALIZER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(SERIALIZER_EXPORTS)
#define SERIALIZER_API Q_DECL_EXPORT
#else
#define SERIALIZER_API Q_DECL_IMPORT
#endif

#endif  // UTILS_SERIALIZER_EXPORT_H
