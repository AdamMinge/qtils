/* ----------------------------------- Local -------------------------------- */
#include "qtils/model/leaf_filter_proxy_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QRegularExpression>
/* -------------------------------------------------------------------------- */

namespace qtils {

QtLeafFilterProxyModel::QtLeafFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

QtLeafFilterProxyModel::~QtLeafFilterProxyModel() = default;

bool QtLeafFilterProxyModel::filterAcceptsRow(
    int source_row, const QModelIndex &source_parent) const {
  const auto source_index = sourceModel()->index(source_row, 0, source_parent);
  if (!source_index.isValid()) return false;

  if (sourceModel()->hasChildren(source_index)) return false;

  if (filterRegularExpression().pattern().isEmpty()) {
    QModelIndex parent_index = source_index.parent();
    if (parent_index.isValid() && !sourceModel()->hasChildren(parent_index))
      return false;

    return true;
  } else {
    const auto match = filterRegularExpression()
                           .match(sourceModel()->data(source_index).toString())
                           .hasMatch();
    if (match) return true;

    QModelIndex parent_index = source_index.parent();
    if (parent_index.isValid() && !sourceModel()->hasChildren(parent_index)) {
      QModelIndex grandparent_index = parent_index.parent();
      while (grandparent_index.isValid()) {
        if (filterRegularExpression()
                .match(sourceModel()->data(parent_index).toString())
                .hasMatch())
          return true;

        parent_index = grandparent_index;
        grandparent_index = parent_index.parent();
      }

      if (filterRegularExpression()
              .match(sourceModel()->data(parent_index).toString())
              .hasMatch())
        return true;

      return false;
    }

    return false;
  }
}

}  // namespace qtils