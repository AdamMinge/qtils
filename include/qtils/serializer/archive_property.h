#ifndef QTILS_SERIALIZER_ARCHIVE_PROPERTY_H
#define QTILS_SERIALIZER_ARCHIVE_PROPERTY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
#include <QVariant>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

template <typename TYPE>
class SERIALIZER_API ArchiveProperty {
 public:
  explicit ArchiveProperty(QString name, TYPE& value);
  ~ArchiveProperty();

  QString getName() const;

  TYPE& getValue() const;
  const TYPE& getConstValue() const;

 private:
  QString m_name;
  TYPE* m_value;
};

template <typename TYPE>
ArchiveProperty<TYPE>::ArchiveProperty(QString name, TYPE& value)
    : m_name(std::move(name)), m_value(std::addressof(value)) {}

template <typename TYPE>
ArchiveProperty<TYPE>::~ArchiveProperty() = default;

template <typename TYPE>
QString ArchiveProperty<TYPE>::getName() const {
  return m_name;
}

template <typename TYPE>
TYPE& ArchiveProperty<TYPE>::getValue() const {
  return *m_value;
}

template <typename TYPE>
const TYPE& ArchiveProperty<TYPE>::getConstValue() const {
  return *m_value;
}

}  // namespace qtils

#endif  // QTILS_SERIALIZER_ARCHIVE_PROPERTY_H
