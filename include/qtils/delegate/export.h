#ifndef QTILS_DELEGATE_EXPORT_H
#define QTILS_DELEGATE_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(DELEGATE_EXPORTS)
#define DELEGATE_API Q_DECL_EXPORT
#else
#define DELEGATE_API Q_DECL_IMPORT
#endif

#endif  // QTILS_DELEGATE_EXPORT_H
