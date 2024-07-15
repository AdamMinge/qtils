#ifndef QTILS_WIDGET_SHORTCUT_SELECTOR_H
#define QTILS_WIDGET_SHORTCUT_SELECTOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/widget/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class WIDGET_API ShortcutSelector : public QLineEdit {
  Q_OBJECT

 public:
  explicit ShortcutSelector(QWidget *parent = nullptr);
  ~ShortcutSelector() override;

 protected:
  void keyPressEvent(QKeyEvent *event) override;
};

}  // namespace qtils

#endif  // QTILS_WIDGET_SHORTCUT_SELECTOR_H
