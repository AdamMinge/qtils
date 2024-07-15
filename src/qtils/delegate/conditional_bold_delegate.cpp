/* ----------------------------------- Local -------------------------------- */
#include "qtils/delegate/conditional_bold_delegate.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QStyleOptionViewItem>
/* -------------------------------------------------------------------------- */

namespace qtils {

QtConditionalBoldDelegate::QtConditionalBoldDelegate(Condition condition,
                                                     QObject *parent)
    : QStyledItemDelegate(parent), m_condition(std::move(condition)) {}

QtConditionalBoldDelegate::~QtConditionalBoldDelegate() = default;

void QtConditionalBoldDelegate::initStyleOption(
    QStyleOptionViewItem *option, const QModelIndex &index) const {
  QStyledItemDelegate::initStyleOption(option, index);

  if (m_condition(index)) {
    option->font.setBold(true);
  }
}

}  // namespace qtils