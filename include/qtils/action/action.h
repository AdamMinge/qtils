#ifndef QTILS_ACTION_ACTION_H
#define QTILS_ACTION_ACTION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/action/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

ACTION_API QAction *createActionWithShortcut(
    const QIcon &icon, QString &text,
    const QKeySequence &key_sequence = QKeySequence{},
    QObject *parent = nullptr);
ACTION_API QAction *createActionWithShortcut(
    const QString &text, const QKeySequence &key_sequence = QKeySequence{},
    QObject *parent = nullptr);
ACTION_API QAction *createActionWithShortcut(
    const QKeySequence &key_sequence = QKeySequence{},
    QObject *parent = nullptr);

}  // namespace qtils

#endif  // QTILS_ACTION_ACTION_H
