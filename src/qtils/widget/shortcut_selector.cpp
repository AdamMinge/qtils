/* ------------------------------------ Qt ---------------------------------- */
#include <QKeyEvent>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/widget/shortcut_selector.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

ShortcutSelector::ShortcutSelector(QWidget *parent) : QLineEdit(parent) {
  setReadOnly(true);
  setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
}

ShortcutSelector::~ShortcutSelector() = default;

void ShortcutSelector::keyPressEvent(QKeyEvent *event) {
  const auto special_keys = std::array<Qt::Key, 4>{
      Qt::Key_Control, Qt::Key_Shift, Qt::Key_Alt, Qt::Key_Meta};

  if (std::find(special_keys.begin(), special_keys.end(), event->key()) ==
      special_keys.end()) {
    QString modifier;
    if (event->modifiers() & Qt::ShiftModifier) modifier += "Shift+";
    if (event->modifiers() & Qt::ControlModifier) modifier += "Ctrl+";
    if (event->modifiers() & Qt::AltModifier) modifier += "Alt+";
    if (event->modifiers() & Qt::MetaModifier) modifier += "Meta+";

    const auto key = QKeySequence(event->key()).toString();
    const auto key_sequence = QKeySequence(modifier + key);
    setText(key_sequence.toString(QKeySequence::NativeText));
  }
}

}  // namespace qtils
