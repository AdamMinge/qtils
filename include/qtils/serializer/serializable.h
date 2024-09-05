#ifndef QTILS_SERIALIZER_SERIALIZABLE_H
#define QTILS_SERIALIZER_SERIALIZABLE_H

/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class OArchive;
class IArchive;

/* ------------------------------- Serializable ----------------------------- */

class SERIALIZER_API Serializable {
 public:
  Serializable();
  virtual ~Serializable();

  virtual void serialize(OArchive &archive) const = 0;
};

/* ------------------------------ Deserializable ---------------------------- */

class SERIALIZER_API Deserializable {
 public:
  Deserializable();
  virtual ~Deserializable();

  virtual void deserialize(IArchive &archive) = 0;
};

}  // namespace qtils

#endif  // QTILS_SERIALIZER_SERIALIZABLE_H
