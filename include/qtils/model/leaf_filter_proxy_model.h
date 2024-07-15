#ifndef QTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H
#define QTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/model/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class MODEL_API QtLeafFilterProxyModel : public QSortFilterProxyModel {
 public:
  QtLeafFilterProxyModel(QObject *parent = nullptr);
  ~QtLeafFilterProxyModel() override;

  bool filterAcceptsRow(int source_row,
                        const QModelIndex &source_parent) const override;
};

}  // namespace qtils

#endif  // QTILS_MODEL_LEAF_FILTER_PROXY_MODEL_H
