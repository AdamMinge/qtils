#ifndef QTILS_STACKED_WIDGET_STACKED_WIDGET_TREE_DELEGATE_H
#define QTILS_STACKED_WIDGET_STACKED_WIDGET_TREE_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/stacked_widget/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class STACKED_WIDGET_API StackedWidgetTreeDelegate
    : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit StackedWidgetTreeDelegate(QObject *parent = nullptr);
  ~StackedWidgetTreeDelegate() override;

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;
  [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override;

  void setMargins(const QMargins &margins);
  [[nodiscard]] const QMargins &getMargins() const;

 private:
  QMargins m_margins;
};

}  // namespace qtils

#endif  // QTILS_STACKED_WIDGET_STACKED_WIDGET_TREE_DELEGATE_H
