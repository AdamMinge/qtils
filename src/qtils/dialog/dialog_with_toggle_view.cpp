/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QActionEvent>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/dialog/dialog_with_toggle_view.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QtDialogWithToggleView::QtDialogWithToggleView(QWidget *parent)
    : QDialog(parent), m_toggle_view(new QAction(this)) {
  m_toggle_view->setCheckable(true);

  connect(m_toggle_view, &QAction::toggled, this,
          &QtDialogWithToggleView::setVisible);
  connect(this, &QtDialogWithToggleView::windowTitleChanged, this,
          &QtDialogWithToggleView::titleChanged);
}
QtDialogWithToggleView::~QtDialogWithToggleView() = default;

QAction *QtDialogWithToggleView::toggleViewAction() const {
  return m_toggle_view;
}

void QtDialogWithToggleView::closeEvent(QCloseEvent *event) {
  QDialog::closeEvent(event);

  if (event->isAccepted()) m_toggle_view->setChecked(false);
}

void QtDialogWithToggleView::titleChanged(const QString &title) {
  m_toggle_view->setText(title);
}

}  // namespace qtils