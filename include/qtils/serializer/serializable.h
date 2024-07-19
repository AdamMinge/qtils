#ifndef QTILS_SERIALIZER_SERIALIZABLE_H
#define QTILS_SERIALIZER_SERIALIZABLE_H

/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class OArchive;
class IArchive;

class SERIALIZER_API Serializable {
 public:
  Serializable() = default;
  virtual ~Serializable() = default;

  virtual void serialize(OArchive &archive) const = 0;
};

class SERIALIZER_API Deserializable {
 public:
  Deserializable() = default;
  virtual ~Deserializable() = default;

  virtual void deserialize(IArchive &archive) = 0;
};

}  // namespace qtils

#endif  // QTILS_SERIALIZER_SERIALIZABLE_H
