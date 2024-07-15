#ifndef QTILS_VIEW_MOUSE_OVER_SELECTABLE_VIEW_H
#define QTILS_VIEW_MOUSE_OVER_SELECTABLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QListView>
#include <QMouseEvent>
#include <QTableView>
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/view/concept.h"
#include "qtils/view/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

template <IsView VIEW>
class VIEW_API QtMouseOverSelectableView : public VIEW {
 public:
  explicit QtMouseOverSelectableView(QWidget *parent = nullptr);
  ~QtMouseOverSelectableView() override;

 protected:
  void mouseMoveEvent(QMouseEvent *event) override;
  void leaveEvent(QEvent *event) override;
};

template <IsView VIEW>
QtMouseOverSelectableView<VIEW>::QtMouseOverSelectableView(QWidget *parent)
    : VIEW(parent) {}

template <IsView VIEW>
QtMouseOverSelectableView<VIEW>::~QtMouseOverSelectableView() = default;

template <IsView VIEW>
void QtMouseOverSelectableView<VIEW>::mouseMoveEvent(QMouseEvent *event) {
  auto item = VIEW::indexAt(event->pos());
  VIEW::setCurrentIndex(QModelIndex{});
  VIEW::setCurrentIndex(item);

  VIEW::mouseMoveEvent(event);
}

template <IsView VIEW>
void QtMouseOverSelectableView<VIEW>::leaveEvent(QEvent *event) {
  VIEW::setCurrentIndex(QModelIndex{});
  VIEW::leaveEvent(event);
}

using QtMouseOverSelectableTreeView = QtMouseOverSelectableView<QTreeView>;
using QtMouseOverSelectableListView = QtMouseOverSelectableView<QListView>;
using QtMouseOverSelectableTableView = QtMouseOverSelectableView<QTableView>;

}  // namespace qtils

#endif  // QTILS_VIEW_MOUSE_OVER_SELECTABLE_VIEW_H
