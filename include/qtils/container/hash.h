#ifndef QTILS_CONTAINER_HASH_H
#define QTILS_CONTAINER_HASH_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/container/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

struct CONTAINER_API QtUuidHash {
  std::size_t operator()(const QUuid& uuid) const {
    return std::hash<std::string>()(uuid.toString().toStdString());
  }
};

}  // namespace qtils

#endif  // QTILS_CONTAINER_HASH_H
