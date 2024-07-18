#ifndef QTILS_SERIALIZER_ARCHIVE_H
#define QTILS_SERIALIZER_ARCHIVE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
#include <QVariant>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/archive_property.h"
#include "qtils/serializer/base_serialization.h"
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class OArchive;
class IArchive;

namespace details {

/* ----------------------------------- IsBase ------------------------------- */

template <typename T>
concept IsBase = std::is_arithmetic_v<T> || std::is_same_v<T, QString>;

/* -------------------------- HasSpecializedSerialize ----------------------- */

template <typename Archive, typename Type>
int serialize(Archive& ar, const Type& value) {
  // static_assert(false, "trying serialize unsupported type");
  return 0;
}

template <typename Type>
concept HasSpecializedSerialize = requires(OArchive& ar, const Type& v) {
  { serialize(ar, v) } -> std::same_as<void>;
};

/* ------------------------- HasSpecializedDeserialize ---------------------- */

template <typename Archive, typename Type>
int deserialize(Archive& ar, Type& value) {
  // static_assert(false, "trying deserialize unsupported type");
  return 0;
}

template <typename Type>
concept HasSpecializedDeserialize = requires(IArchive& ar, Type& v) {
  { deserialize(ar, v) } -> std::same_as<void>;
};

/* -------------------------------- IteratorType ---------------------------- */

template <typename T>
struct IteratorType {
  using type = typename T::iterator;
};

template <typename T>
struct IteratorType<const T> {
  using type = typename T::const_iterator;
};

/* --------------------------------- IsString ------------------------------- */

template <typename T>
concept IsString = std::is_same_v<T, QString>;

/* -------------------------------- IsContainer ----------------------------- */

template <typename T>
concept IsContainer = requires(T object) {
  typename T::value_type;
  typename T::iterator;
  typename T::const_iterator;
  { object.begin() } -> std::same_as<typename IteratorType<T>::type>;
  { object.end() } -> std::same_as<typename IteratorType<T>::type>;
  { object.cbegin() } -> std::same_as<typename T::const_iterator>;
  { object.cend() } -> std::same_as<typename T::const_iterator>;
};

/* ---------------------------- IsResizableContainer ------------------------ */

template <typename T>
concept IsResizableContainer = requires(T& object) {
  {object.resize(std::declval<typename T::size_type>())};
}
&&IsContainer<T>;

/* ---------------------------- IsMappingContainer -------------------------- */

template <typename T>
concept IsMappingContainer = requires(T object) {
  typename T::key_type;
  typename T::mapped_type;
  { object.begin() } -> std::same_as<typename IteratorType<T>::type>;
  { object.end() } -> std::same_as<typename IteratorType<T>::type>;
  { object.cbegin() } -> std::same_as<typename T::const_iterator>;
  { object.cend() } -> std::same_as<typename T::const_iterator>;
};

/* ------------------------------ IsDereferenceable ------------------------- */

template <typename T>
concept IsDereferenceable = requires(T object) {
  {
    *std::declval<T>()
    } -> std::same_as<
        typename std::add_lvalue_reference<decltype(*std::declval<T>())>::type>;
};
/* ------------------------------- IsSerializable --------------------------- */

template <typename T>
concept IsSerializable = requires(const T& object, OArchive& s) {
  {
    std::invoke(&T::serialize, std::declval<T>(), std::declval<OArchive&>())
    } -> std::same_as<void>;
};

/* ------------------------------ IsDeserializable -------------------------- */

template <typename T>
concept IsDeserializable = requires(T& object, IArchive& s) {
  {
    std::invoke(&T::deserialize, std::declval<T>(), std::declval<IArchive&>())
    } -> std::same_as<void>;
};

}  // namespace details

/* --------------------------------- OArchive ------------------------------- */

class SERIALIZER_API OArchive {
 public:
  explicit OArchive() = default;
  virtual ~OArchive() = default;

  template <typename TYPE>
  OArchive& operator<<(const ArchiveProperty<TYPE>& property);

  template <typename TYPE>
  OArchive& operator<<(const TYPE& value);

 protected:
  virtual void saveStart(const QString& name) = 0;
  virtual void saveEnd(const QString& name) = 0;

  virtual void arrayStart(qsizetype i) = 0;
  virtual void arrayEnd(qsizetype i) = 0;

  virtual void save(const QVariant& value) = 0;

 private:
  template <typename TYPE>
  void serialize(const TYPE& value);
  template <details::HasSpecializedSerialize TYPE>
  void serializeCustom(const TYPE& object);
  template <details::IsDereferenceable TYPE>
  void serializeReference(const TYPE& object);
  template <details::IsSerializable TYPE>
  void serializeObject(const TYPE& object);
  template <details::IsContainer TYPE>
  void serializeContainer(const TYPE& container);
  template <details::IsMappingContainer TYPE>
  void serializeMappingContainer(const TYPE& container);
  template <typename TYPE>
  void serializeBase(const TYPE& value);
};

template <typename TYPE>
OArchive& OArchive::operator<<(const ArchiveProperty<TYPE>& property) {
  saveStart(property.getName());
  (*this) << property.getConstValue();
  saveEnd(property.getName());

  return *this;
}

template <typename TYPE>
OArchive& OArchive::operator<<(const TYPE& value) {
  serialize(value);

  return *this;
}

template <typename TYPE>
void OArchive::serialize(const TYPE& value) {
  if constexpr (details::HasSpecializedSerialize<TYPE>)
    serializeCustom(value);
  else if constexpr (details::IsSerializable<TYPE>)
    serializeObject(value);
  else if constexpr (details::IsMappingContainer<TYPE>)
    serializeMappingContainer(value);
  else if constexpr (details::IsContainer<TYPE> && !details::IsString<TYPE>)
    serializeContainer(value);
  else if constexpr (details::IsDereferenceable<TYPE>)
    serializeReference(value);
  else
    serializeBase(value);
}

template <details::HasSpecializedSerialize TYPE>
void OArchive::serializeCustom(const TYPE& object) {
  qtils::serialize(*this, object);
}

template <details::IsDereferenceable TYPE>
void OArchive::serializeReference(const TYPE& object) {
  serialize(*object);
}

template <details::IsSerializable TYPE>
void OArchive::serializeObject(const TYPE& object) {
  object.serialize(*this);
}

template <details::IsContainer TYPE>
void OArchive::serializeContainer(const TYPE& container) {
  auto index = 0;
  for (const auto& value : container) {
    arrayStart(index);
    serialize(value);
    arrayEnd(index);

    index += 1;
  }
}

template <details::IsMappingContainer TYPE>
void OArchive::serializeMappingContainer(const TYPE& container) {
  for (auto it = container.begin(); it != container.end(); ++it) {
    const auto& key = it.key();
    const auto& value = it.value();
    (*this) << ArchiveProperty(key, value);
  }
}

template <typename TYPE>
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

  template <typename TYPE>
  IArchive& operator>>(TYPE& value);

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
  template <details::HasSpecializedDeserialize TYPE>
  void deserializeCustom(TYPE& object);
  template <details::IsDereferenceable TYPE>
  void deserializeReference(TYPE& object);
  template <details::IsSerializable TYPE>
  void deserializeObject(TYPE& object);
  template <details::IsResizableContainer TYPE>
  void deserializeContainer(TYPE& container);
  template <details::IsMappingContainer TYPE>
  void deserializeMappingContainer(TYPE& container);
  template <typename TYPE>
  void deserializeBase(TYPE& value);
};

template <typename TYPE>
IArchive& IArchive::operator>>(const ArchiveProperty<TYPE>& property) {
  loadStart(property.getName());
  (*this) >> property.getValue();
  loadEnd(property.getName());

  return *this;
}

template <typename TYPE>
IArchive& IArchive::operator>>(TYPE& value) {
  deserialize(value);

  return *this;
}

template <typename TYPE>
void IArchive::deserialize(TYPE& value) {
  if constexpr (details::HasSpecializedDeserialize<TYPE>)
    deserializeCustom(value);
  else if constexpr (details::IsSerializable<TYPE>)
    deserializeObject(value);
  else if constexpr (details::IsMappingContainer<TYPE>)
    deserializeMappingContainer(value);
  else if constexpr (details::IsResizableContainer<TYPE> &&
                     !details::IsString<TYPE>)
    deserializeContainer(value);
  else if constexpr (details::IsDereferenceable<TYPE>)
    deserializeReference(value);
  else
    deserializeBase(value);
}

template <details::HasSpecializedDeserialize TYPE>
void IArchive::deserializeCustom(TYPE& object) {
  qtils::deserialize(*this, object);
}

template <details::IsDereferenceable TYPE>
void IArchive::deserializeReference(TYPE& object) {
  deserialize(*object);
}

template <details::IsSerializable TYPE>
void IArchive::deserializeObject(TYPE& object) {
  object.deserialize(*this);
}

template <details::IsResizableContainer TYPE>
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

template <details::IsMappingContainer TYPE>
void IArchive::deserializeMappingContainer(TYPE& container) {
  const auto names = getChildNames();
  for (const auto& name : names) {
    auto value = typename TYPE::mapped_type{};
    (*this) >> ArchiveProperty(name, value);

    container[name] = value;
  }
}

template <typename TYPE>
void IArchive::deserializeBase(TYPE& value) {
  value = load().value<TYPE>();
}

}  // namespace qtils

#endif  // QTILS_SERIALIZER_ARCHIVE_H
