#ifndef QTILS_POINTER_UNIQUE_PTR_CAST_H
#define QTILS_POINTER_UNIQUE_PTR_CAST_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/pointer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

template <typename TO, typename FROM>
std::unique_ptr<TO> POINTER_API cast_unique_ptr(std::unique_ptr<FROM> &&from) {
  return std::unique_ptr<TO>(dynamic_cast<TO *>(from.release()));
}

}  // namespace qtils

#endif  // QTILS_POINTER_UNIQUE_PTR_CAST_H
