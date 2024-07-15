#ifndef QTILS_SERIALIZER_ARCHIVE_H
#define QTILS_SERIALIZER_ARCHIVE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
#include <QVariant>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/archive_property.h"
#include "qtils/serializer/base_serialization.h"
#include "qtils/serializer/concept.h"
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

/* --------------------------------- OArchive ------------------------------- */

class SERIALIZER_API OArchive {
 public:
  explicit OArchive() = default;
  virtual ~OArchive() = default;

  template <typename TYPE>
  OArchive& operator<<(const ArchiveProperty<TYPE>& property);

 protected:
  virtual void saveStart(const QString& name) = 0;
  virtual void saveEnd(const QString& name) = 0;

  virtual void arrayStart(qsizetype i) = 0;
  virtual void arrayEnd(qsizetype i) = 0;

  virtual void save(const QVariant& value) = 0;

 private:
  template <typename TYPE>
  void serialize(const TYPE& value);
  template <HasSpecializedSerialize TYPE>
  void serializeCustom(const TYPE& object);
  template <IsDereferenceable TYPE>
  void serializeReference(const TYPE& object);
  template <IsSerializable TYPE>
  void serializeObject(const TYPE& object);
  template <IsContainer TYPE>
  void serializeContainer(const TYPE& container);
  template <IsMappingContainer TYPE>
  void serializeMappingContainer(const TYPE& container);
  template <IsBase TYPE>
  void serializeBase(const TYPE& value);
};

template <typename TYPE>
OArchive& OArchive::operator<<(const ArchiveProperty<TYPE>& property) {
  saveStart(property.getName());
  serialize(property.getConstValue());
  saveEnd(property.getName());

  return *this;
}

template <typename TYPE>
void OArchive::serialize(const TYPE& value) {
  if constexpr (HasSpecializedSerialize<TYPE>)
    serializeCustom(value);
  else if constexpr (IsSerializable<TYPE>)
    serializeObject(value);
  else if constexpr (IsMappingContainer<TYPE>)
    serializeMappingContainer(value);
  else if constexpr (IsContainer<TYPE> && !IsString<TYPE>)
    serializeContainer(value);
  else if constexpr (IsDereferenceable<TYPE>)
    serializeReference(value);
  else
    serializeBase(value);
}

template <HasSpecializedSerialize TYPE>
void OArchive::serializeCustom(const TYPE& object) {
  qtils::serialize(*this, object);
}

template <IsDereferenceable TYPE>
void OArchive::serializeReference(const TYPE& object) {
  serialize(*object);
}

template <IsSerializable TYPE>
void OArchive::serializeObject(const TYPE& object) {
  object.serialize(*this);
}

template <IsContainer TYPE>
void OArchive::serializeContainer(const TYPE& container) {
  auto index = 0;
  for (const auto& value : container) {
    arrayStart(index);
    serialize(value);
    arrayEnd(index);

    index += 1;
  }
}

template <IsMappingContainer TYPE>
void OArchive::serializeMappingContainer(const TYPE& container) {
  for (auto it = container.begin(); it != container.end(); ++it) {
    const auto& key = it.key();
    const auto& value = it.value();
    (*this) << ArchiveProperty(key, value);
  }
}

template <IsBase TYPE>
void OArchive::serializeBase(const TYPE& value) {
  save(QVariant::fromValue<TYPE>(value));
}

/* --------------------------------- IArchive ------------------------------- */

class SERIALIZER_API IArchive {
 public:
  explicit IArchive() = default;
  virtual ~IArchive() = default;

  template <typename TYPE>
  IArchive& operator>>(const ArchiveProperty<TYPE>& property);

 protected:
  virtual void loadStart(const QString& name) = 0;
  virtual void loadEnd(const QString& name) = 0;

  virtual void arrayStart(qsizetype i) = 0;
  virtual void arrayEnd(qsizetype i) = 0;

  virtual QVariant load() = 0;

  [[nodiscard]] virtual QStringList getChildNames() const = 0;
  [[nodiscard]] virtual qsizetype getChildCount() const = 0;

 private:
  template <typename TYPE>
  void deserialize(TYPE& value);
  template <HasSpecializedDeserialize TYPE>
  void deserializeCustom(TYPE& object);
  template <IsDereferenceable TYPE>
  void deserializeReference(TYPE& object);
  template <IsSerializable TYPE>
  void deserializeObject(TYPE& object);
  template <IsResizableContainer TYPE>
  void deserializeContainer(TYPE& container);
  template <IsMappingContainer TYPE>
  void deserializeMappingContainer(TYPE& container);
  template <IsBase TYPE>
  void deserializeBase(TYPE& value);
};

template <typename TYPE>
IArchive& IArchive::operator>>(const ArchiveProperty<TYPE>& property) {
  loadStart(property.getName());
  deserialize(property.getValue());
  loadEnd(property.getName());

  return *this;
}

template <typename TYPE>
void IArchive::deserialize(TYPE& value) {
  if constexpr (HasSpecializedDeserialize<TYPE>)
    deserializeCustom(value);
  else if constexpr (IsSerializable<TYPE>)
    deserializeObject(value);
  else if constexpr (IsMappingContainer<TYPE>)
    deserializeMappingContainer(value);
  else if constexpr (IsResizableContainer<TYPE> && !IsString<TYPE>)
    deserializeContainer(value);
  else if constexpr (IsDereferenceable<TYPE>)
    deserializeReference(value);
  else
    deserializeBase(value);
}

template <HasSpecializedDeserialize TYPE>
void IArchive::deserializeCustom(TYPE& object) {
  qtils::deserialize(*this, object);
}

template <IsDereferenceable TYPE>
void IArchive::deserializeReference(TYPE& object) {
  deserialize(*object);
}

template <IsSerializable TYPE>
void IArchive::deserializeObject(TYPE& object) {
  object.deserialize(*this);
}

template <IsResizableContainer TYPE>
void IArchive::deserializeContainer(TYPE& container) {
  container.resize(getChildCount());

  auto index = 0;
  for (auto& value : container) {
    arrayStart(index);
    deserialize(value);
    arrayEnd(index);

    index += 1;
  }
}

template <IsMappingContainer TYPE>
void IArchive::deserializeMappingContainer(TYPE& container) {
  const auto names = getChildNames();
  for (const auto& name : names) {
    auto value = typename TYPE::mapped_type{};
    (*this) >> ArchiveProperty(name, value);

    container[name] = value;
  }
}

template <IsBase TYPE>
void IArchive::deserializeBase(TYPE& value) {
  value = load().value<TYPE>();
}

}  // namespace qtils

#endif  // QTILS_SERIALIZER_ARCHIVE_H
