#ifndef QTILS_VIEW_UNSELECTABLE_VIEW_H
#define QTILS_VIEW_UNSELECTABLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QListView>
#include <QMouseEvent>
#include <QTableView>
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/view/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
class VIEW_API QtUnselectableView : public VIEW {
 public:
  explicit QtUnselectableView(QWidget *parent = nullptr);
  ~QtUnselectableView() override;

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void focusOutEvent(QFocusEvent *event) override;
};

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
QtUnselectableView<VIEW>::QtUnselectableView(QWidget *parent) : VIEW(parent) {}

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
    QtUnselectableView<VIEW>::~QtUnselectableView() = default;

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
void QtUnselectableView<VIEW>::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::RightButton) {
    auto item = VIEW::indexAt(event->pos());

    if (auto selection_model = VIEW::selectionModel()) {
      auto selected = selection_model && selection_model->isSelected(item);
      if ((item.row() == -1 && item.column() == -1) || selected) {
        VIEW::selectionModel()->setCurrentIndex(
            QModelIndex(), QItemSelectionModel::ClearAndSelect);
      }
    }
  }

  VIEW::mousePressEvent(event);
}

template <typename VIEW>
requires std::derived_from<VIEW, QAbstractItemView>
void QtUnselectableView<VIEW>::focusOutEvent(QFocusEvent *event) {
  if (event->reason() != Qt::PopupFocusReason) {
    if (auto selection_model = VIEW::selectionModel()) {
      selection_model->setCurrentIndex(QModelIndex(),
                                       QItemSelectionModel::ClearAndSelect);
    }
  }

  VIEW::focusOutEvent(event);
}

using QtUnselectableTreeView = QtUnselectableView<QTreeView>;
using QtUnselectableListView = QtUnselectableView<QListView>;
using QtUnselectableTableView = QtUnselectableView<QTableView>;

}  // namespace qtils

#endif  // QTILS_VIEW_UNSELECTABLE_VIEW_H
