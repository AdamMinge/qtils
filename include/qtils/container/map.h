#ifndef QTILS_CONTAINER_MAP_H
#define QTILS_CONTAINER_MAP_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ------------------------------------- Qt --------------------------------- */
#include <QMap>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/container/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

template <typename VALUE, typename KEYS>
QMap<typename std::decay_t<KEYS>::value_type, VALUE> mapFromKeys(KEYS&& keys,
                                                                 VALUE value) {
  auto map = QMap<typename std::decay_t<KEYS>::value_type, VALUE>{};
  for (auto&& key : std::forward<KEYS>(keys)) {
    map[key] = value;
  }

  return map;
}

}  // namespace qtils

#endif  // QTILS_CONTAINER_MAP_H
