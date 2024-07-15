#ifndef UTILS_MODEL_EXPORT_H
#define UTILS_MODEL_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(MODEL_EXPORTS)
#define MODEL_API Q_DECL_EXPORT
#else
#define MODEL_API Q_DECL_IMPORT
#endif

#endif  // UTILS_MODEL_EXPORT_H
