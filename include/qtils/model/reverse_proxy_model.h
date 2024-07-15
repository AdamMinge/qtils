#ifndef QTILS_MODEL_REVERSE_PROXY_MODEL_H
#define QTILS_MODEL_REVERSE_PROXY_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/model/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class MODEL_API QtReverseProxyModel : public QSortFilterProxyModel {
 public:
  QtReverseProxyModel(QObject *parent = nullptr);
  ~QtReverseProxyModel() override;

 protected:
  bool lessThan(const QModelIndex &source_left,
                const QModelIndex &source_right) const override;
};

}  // namespace qtils

#endif  // QTILS_MODEL_REVERSE_PROXY_MODEL_H
