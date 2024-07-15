/* ----------------------------------- Local -------------------------------- */
#include "qtils/model/cast.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QModelIndex mapToSourceIndex(const QModelIndex& index,
                             QAbstractItemModel* model) {
  auto proxy_model = qobject_cast<QSortFilterProxyModel*>(model);
  if (proxy_model) return mapToSourceIndex(index, proxy_model);
  return index;
}

QModelIndex mapToSourceIndex(const QModelIndex& proxy_index,
                             QSortFilterProxyModel* proxy_model) {
  const auto source_index = proxy_model->mapToSource(proxy_index);
  auto parent_proxy_model =
      qobject_cast<QSortFilterProxyModel*>(proxy_model->sourceModel());

  if (parent_proxy_model)
    return mapToSourceIndex(source_index, parent_proxy_model);

  return source_index;
}

QModelIndex mapFromSourceIndex(const QModelIndex& index,
                               QAbstractItemModel* model) {
  auto proxy_model = qobject_cast<QSortFilterProxyModel*>(model);
  if (proxy_model) return mapFromSourceIndex(index, proxy_model);
  return index;
}

QModelIndex mapFromSourceIndex(const QModelIndex& source_index,
                               QSortFilterProxyModel* proxy_model) {
  auto index = source_index;
  auto parent_proxy_model =
      qobject_cast<QSortFilterProxyModel*>(proxy_model->sourceModel());
  if (parent_proxy_model) {
    index = mapFromSourceIndex(source_index, parent_proxy_model);
  }

  return proxy_model->mapFromSource(index);
}

}  // namespace qtils