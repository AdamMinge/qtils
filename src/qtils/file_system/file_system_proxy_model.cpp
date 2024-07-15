/* ------------------------------------ Qt ---------------------------------- */
#include <QFileSystemModel>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/file_system/file_system_proxy_model.h"
/* -------------------------------------------------------------------------- */

namespace qtils {
FileSystemProxyModel::FileSystemProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

FileSystemProxyModel::~FileSystemProxyModel() = default;

bool FileSystemProxyModel::dropMimeData(const QMimeData *data,
                                        Qt::DropAction action, int row,
                                        int column, const QModelIndex &parent) {
  auto model = qobject_cast<QFileSystemModel *>(sourceModel());
  if (model) {
    auto root_path = model->rootPath();
    auto root_index = model->index(root_path).parent();
    auto source_parent = mapToSource(parent);

    if (root_index == source_parent) {
      auto new_parent = mapFromSource(model->index(root_path));
      return QSortFilterProxyModel::dropMimeData(data, action, row, column,
                                                 new_parent);
    }
  }

  return QSortFilterProxyModel::dropMimeData(data, action, row, column, parent);
}

bool FileSystemProxyModel::filterAcceptsRow(
    int source_row, const QModelIndex &source_parent) const {
  auto model = qobject_cast<QFileSystemModel *>(sourceModel());
  auto index = model->index(source_row, 0, source_parent);
  auto rootIndex = model->index(model->rootPath());

  if (!rootIndex.isValid()) return false;

  return (index.isValid() && index == rootIndex) ||
         !isSiblingOf(index, rootIndex);
}

bool FileSystemProxyModel::isSiblingOf(const QModelIndex &index,
                                       const QModelIndex &parent) const {
  if (!index.isValid() || !parent.isValid()) return false;

  QModelIndex sibling;
  int row = 0;
  do {
    sibling = parent.sibling(row, 0);
    if (sibling == index) return true;

    ++row;

  } while (sibling.isValid());

  return false;
}

}  // namespace qtils
