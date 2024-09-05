#ifndef QTILS_DELEGATE_CONDITIONAL_BOLD_DELEGATE_H
#define QTILS_DELEGATE_CONDITIONAL_BOLD_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/delegate/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class DELEGATE_API QtConditionalBoldDelegate : public QStyledItemDelegate {
 public:
  using Condition = std::function<bool(const QModelIndex &)>;

 public:
  explicit QtConditionalBoldDelegate(Condition condition,
                                     QObject *parent = nullptr);
  ~QtConditionalBoldDelegate() override;

 protected:
  void initStyleOption(QStyleOptionViewItem *option,
                       const QModelIndex &index) const override;

 private:
  Condition m_condition;
};

}  // namespace qtils

#endif  // QTILS_DELEGATE_CONDITIONAL_BOLD_DELEGATE_H
