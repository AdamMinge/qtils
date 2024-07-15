/* ----------------------------------- Local -------------------------------- */
#include "qtils/action/action.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QAction *createActionWithShortcut(const QIcon &icon, QString &text,
                                  const QKeySequence &key_sequence,
                                  QObject *parent) {
  auto action = std::make_unique<QAction>(icon, text, parent);
  if (!key_sequence.isEmpty()) action->setShortcut(key_sequence);

  return action.release();
}

QAction *createActionWithShortcut(const QString &text,
                                  const QKeySequence &key_sequence,
                                  QObject *parent) {
  auto action = std::make_unique<QAction>(text, parent);
  if (!key_sequence.isEmpty()) action->setShortcut(key_sequence);

  return action.release();
}

QAction *createActionWithShortcut(const QKeySequence &key_sequence,
                                  QObject *parent) {
  auto action = std::make_unique<QAction>(parent);
  if (!key_sequence.isEmpty()) action->setShortcut(key_sequence);

  return action.release();
}

}  // namespace qtils