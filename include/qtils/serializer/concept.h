#ifndef QTILS_SERIALIZER_CONCEPT_H
#define QTILS_SERIALIZER_CONCEPT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QVariant>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class OArchive;
class IArchive;

/* ----------------------------------- IsBase ------------------------------- */

template <typename T>
concept IsBase = requires(T value) {
  {QVariant::fromValue<T>(value)};
};

/* -------------------------- HasSpecializedSerialize ----------------------- */

template <typename T>
int serialize(OArchive &ar, const T &value) {
  return 0;
}

template <typename T>
concept HasSpecializedSerialize = requires(OArchive &ar, const T &v) {
  { serialize(ar, v) } -> std::same_as<void>;
};

/* ------------------------- HasSpecializedDeserialize ---------------------- */

template <typename T>
int deserialize(OArchive &ar, T &value) {
  return 0;
}

template <typename T>
concept HasSpecializedDeserialize = requires(IArchive &ar, T &v) {
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
concept IsResizableContainer = requires(T &object) {
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
concept IsSerializable = requires(const T &object, OArchive &s) {
  {
    std::invoke(&T::serialize, std::declval<T>(), std::declval<OArchive &>())
    } -> std::same_as<void>;
};

/* ------------------------------ IsDeserializable -------------------------- */

template <typename T>
concept IsDeserializable = requires(T &object, IArchive &s) {
  {
    std::invoke(&T::deserialize, std::declval<T>(), std::declval<IArchive &>())
    } -> std::same_as<void>;
};

}  // namespace qtils

#endif  // QTILS_SERIALIZER_CONCEPT_H
